#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct file_info {
    int lines;
    int words;
    int bytes;
};

struct file_info get_file_info(FILE *file) {
    int lines = 0, words = 0, bytes = 0;

    int c;
    bool in_word = false;
    while ((c = fgetc(file)) != EOF) {
        ++bytes;

        if (c == '\n' || c == '\0') {
            ++lines;
            in_word = false;
        } else if (c == ' ' || c == '\t') {
            in_word = false;
        } else {
            if (!in_word) {
                ++words;
            }
            in_word = true;
        }
    }

    struct file_info file_info = { lines + 1, words, bytes };
    return file_info;
}


int main(int argc, char *argv[]) {
    // program name + filename
    assert(argc >= 2);

    bool flag_l = false, flag_w = false, flag_c = false;

    const char *short_options = "lwc";

    const struct option long_options[] = {
            { "lines", no_argument, NULL, 'l' },
            { "words", no_argument, NULL, 'w' },
            { "bytes", no_argument, NULL, 'c' },
            { "help", no_argument, NULL, 'h' },
            { NULL, 0, NULL, 0 }
    };

    int opt, opt_index = 0;
    while ((opt = getopt_long(argc, argv, short_options, long_options, &opt_index)) != -1) {
        switch (opt) {
            case 'l':
                flag_l = true;
                break;
            case 'w':
                flag_w = true;
                break;
            case 'c':
                flag_c = true;
                break;
            case 'h':
                printf("Usage: %s [-lwc] [--lines] [--words] [--bytes]\n", argv[0]);
                break;
            case '?':
                printf("Usage: %s [-lwc] [--lines] [--words] [--bytes]\n", argv[0]);
                exit(EXIT_FAILURE);
            default:
                printf("Unexpected problem!\n");
                exit(EXIT_FAILURE);
        }
    }

    const char *filename = argv[argc - 1];

    printf("Getting info for file %s...\n", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File opening failed!\n");
        exit(EXIT_FAILURE);
    }

    struct file_info file_info = get_file_info(file);

    if (!flag_l && !flag_w && !flag_c) {
        printf("No info about the file %s was asked!\n", filename);
    } else {
        printf("%s file info:\n", filename);

        if (flag_l) {
            printf("Lines count: %d\n", file_info.lines);
        }

        if (flag_w) {
            printf("Words count: %d\n", file_info.words);
        }

        if (flag_c) {
            printf("Bytes: %d\n", file_info.bytes);
        }
    }

    return 0;
}