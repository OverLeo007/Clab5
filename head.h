typedef struct {
    int length;
    char *name;
    int min_depth;
    int passability_lvl;
} river;

unsigned char *pick_ffields();

void print_filters(unsigned char *filters, river *r_array, river *end_ptr);

int save(river *st, int rivers_count);

int load();

void add_river(int length, char *name, int depth, river **end_ptr);

void delete_river(int river_num, river *r_array, river **end_ptr);

void print_river(river *my_river);

void print_rivers(river *r_array, river *end_ptr);

int compare_names(const void* river1, const void* river2);

int compare_lens(const void* river1, const void* river2);

int compare_depths(const void* river1, const void* river2);

int compare_pass(const void* river1, const void* river2);