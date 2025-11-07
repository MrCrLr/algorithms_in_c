#include "btvt_fileio.h"

static inline void get_executable_dir(char *out, size_t size) {
    char exe_path[PATH_MAX] = {0};

#ifdef __APPLE__
    uint32_t len = sizeof(exe_path);
    if (_NSGetExecutablePath(exe_path, &len) != 0) {
        fprintf(stderr, "_NSGetExecutablePath: buffer too small\n");
        exit(EXIT_FAILURE);
    }
    realpath(exe_path, exe_path);  // resolve symlinks
#else
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
    exe_path[len] = '\0';
#endif

    // Trim to directory
    char *dir = dirname(exe_path);
    snprintf(out, size, "%s", dir);
}

static inline char *get_project_path(void) {
    static char path[PATH_MAX];
    char dir[PATH_MAX];
    get_executable_dir(dir, sizeof(dir));

    // Remove trailing /build if present
    char *last = strrchr(dir, '/');
    if (last && strcmp(last + 1, "build") == 0) {
        *last = '\0';
    }
    if (dir[0] == '\0' || strcmp(dir, "/") == 0) {
        if (getcwd(dir, sizeof(dir)) == NULL) {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
    }

    snprintf(path, sizeof(path), "%s/img", dir);
    return path;
}

static inline void ensure_dir(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return;
        fprintf(stderr, "Error: %s exists and is not a directory\n", path);
        exit(EXIT_FAILURE);
    }
    if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
}

static inline FILE *open_project_file(const char *filename, const char *subdir, const char *mode) {
    if (!filename || !mode) {
        fprintf(stderr, "Invalid arguments to open_project_file\n");
        return NULL;
    }

    const char *basedir = get_project_path(); // or general project root resolver
    ensure_dir(basedir);

    char dirpath[PATH_MAX];
    if (subdir && *subdir) {
        snprintf(dirpath, sizeof(dirpath), "%s/%s", basedir, subdir);
        ensure_dir(dirpath);
    } else {
        snprintf(dirpath, sizeof(dirpath), "%s", basedir);
    }

    char filepath[PATH_MAX];
    int rc = snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, filename);
    if (rc <= 0 || (size_t)rc >= sizeof(filepath)) {
        fprintf(stderr, "Filename too long\n");
        return NULL;
    }

    FILE *f = fopen(filepath, mode);
    if (!f) {
        perror("fopen");
        return NULL;
    }
    return f;
}

static inline int bmp_pad_bytes(int width, int bytes_per_pixel) {
    return (4 - (width * bytes_per_pixel) % 4) % 4;
}

static inline void write_u32_le(uint8_t *b, uint32_t v) {
    b[0] = (uint8_t)(v & 0xFF);
    b[1] = (uint8_t)((v >> 8) & 0xFF);
    b[2] = (uint8_t)((v >> 16) & 0xFF);
    b[3] = (uint8_t)((v >> 24) & 0xFF);
}

static inline void write_bmp_headers(FILE *f, int width, int height, int bits_per_pixel) {
    const int bytes_per_pixel = bits_per_pixel / 8;
    uint32_t row_size = (uint32_t)(width * bytes_per_pixel + 3) & (~3); // bitmask zeroes out lower 2 bits
    uint32_t pixel_array_size = row_size * (uint32_t)height;
    uint32_t file_size = 14u + 40u + pixel_array_size;

    // --- BITMAPFILEHEADER (14 bytes) ---
    uint8_t file_header[14] = { 'B', 'M', 0 };
    write_u32_le(&file_header[2], file_size);
    // reserved 4 bytes are zero
    write_u32_le(&file_header[10], 14u + 40u);
    fwrite(file_header, 1, sizeof(file_header), f);

    // --- BITMAPINFOHEADER (40 bytes) ---
    uint8_t info_header[40] = {0};
    write_u32_le(&info_header[0], 40u);
    write_u32_le(&info_header[4], width);
    write_u32_le(&info_header[8], height);
    info_header[12] = 1; 
    write_u32_le(&info_header[14], (uint32_t)bits_per_pixel);
    fwrite(info_header, 1, sizeof(info_header), f);
}

void write_bmp(const char *filename, image_t *img) {
    if (!filename || !img || img->w <= 0 || img->h <= 0) {
        fprintf(stderr, "Invalid arguments to write_bmp\n");
        return;
    }

    FILE *f = open_project_file(filename, NULL, "wb");
    if (!f) return;
    
    const int bits_per_pixel = 24;
    write_bmp_headers(f, img->w, img->h, bits_per_pixel);
    
    const int bytes_per_pixel = bits_per_pixel / 8;
    uint8_t pad[3] = {0, 0, 0};
    int pad_bytes = bmp_pad_bytes(img->w, bytes_per_pixel);

    for (int y = img->h - 1; y >= 0; y--) {
        pixel *row = &img->data[y * img->w];
        fwrite(row, bytes_per_pixel, img->w, f);
        if (pad_bytes) 
            fwrite(pad, 1, pad_bytes, f);
    }

    fclose(f);
}


