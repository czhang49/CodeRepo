typedef struct {
    int shift;
    char * line;
    double chi_square;
} cipher;

// Shifts all the characters in a null terminated c string
// after lowercasing all the characters
// it is up to the caller to free the memory allocated.
char * shift_line(char * line, int shift);

// Brute forces all the possible shifts and returns an array of char pointers
// where the i-th index refers to the line shifted by i
char ** brute_cipher(char * line);

// Generates the chi-square value for the characters in the line.
// For those curious:
// chi_square = sum from a to z of (observed_i - expected_i)^2/ expected_i;
double chi_square(char * line);

// Determines which line is more likely based a chi-square value.
int likeness(const void* a, const void* b);

// Returns an array of ciphers in order of
// most likely according to the relative frequencies of english characters.
// It is the callers job to free the ciphers.
cipher * sorted_shifts(char * line);

// Returns a string representing the printof of the first n ciphers.
// It is up to the caller to free the memory allocated for the string.
char * get_cipher_print_out(cipher * ciphers, int n, char * line);

// Returns a string representing the printof of the ciphers generated from the line.
// It is up to the caller to free the memory allocated for the string.
char * get_print_out(char * line);

// Returns a string representing the printof of the most likely cipher generated from the line.
// It is up to the caller to free the memory allocated for the string.
char * get_most_likely_print_out(char * line);
