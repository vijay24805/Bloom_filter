#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BLK_SZ 250000
#define BLK_NMEMB 8
#define MAXP 46337  /* prime, and 46337*46337 < 2147483647 */

/* Used to create 8 different hash functions */
int b[8];

int v0[256];
int v1[256];
int v2[256];
int v3[256];
int v4[256];
int v5[256];
int v6[256];
int v7[256];

typedef struct bloom {
	char block0[BLK_SZ];
	char block1[BLK_SZ];
	char block2[BLK_SZ];
	char block3[BLK_SZ];
	char block4[BLK_SZ];
	char block5[BLK_SZ];
	char block6[BLK_SZ];
	char block7[BLK_SZ];
} bf_t;

void sample_string_A(char *s, long i) {
	s[0] = (char) (1 + (i % 254));
	s[1] = (char) (1 + ((i / 254) % 254));
	s[2] = (char) (1 + (((i / 254) / 254) % 254));
	s[3] = 'a';
	s[4] = 'b';
	s[5] = (char) (1 + ((i * (i - 3)) % 217));
	s[6] = (char) (1 + ((17 * i + 129) % 233));
	s[7] = '\0';
}
void sample_string_B(char *s, long i) {
	s[0] = (char) (1 + (i % 254));
	s[1] = (char) (1 + ((i / 254) % 254));
	s[2] = (char) (1 + (((i / 254) / 254) % 254));
	s[3] = 'a';
	s[4] = (char) (1 + ((i * (i - 3)) % 217));
	s[5] = (char) (1 + ((17 * i + 129) % 233));
	s[6] = '\0';
}
void sample_string_C(char *s, long i) {
	s[0] = (char) (1 + (i % 254));
	s[1] = (char) (1 + ((i / 254) % 254));
	s[2] = 'a';
	s[3] = (char) (1 + ((i * (i - 3)) % 217));
	s[4] = (char) (1 + ((17 * i + 129) % 233));
	s[5] = '\0';
}
void sample_string_D(char *s, long i) {
	s[0] = (char) (1 + (i % 254));
	s[1] = (char) (1 + ((i / 254) % 254));
	s[2] = (char) (1 + (((i / 254) / 254) % 254));
	s[3] = 'b';
	s[4] = 'b';
	s[5] = (char) (1 + ((i * (i - 3)) % 217));
	s[6] = (char) (1 + ((17 * i + 129) % 233));
	s[7] = '\0';
}
void sample_string_E(char *s, long i) {
	s[0] = (char) (1 + (i % 254));
	s[1] = (char) (1 + ((i / 254) % 254));
	s[2] = (char) (1 + (((i / 254) / 254) % 254));
	s[3] = 'a';
	s[4] = (char) (2 + ((i * (i - 3)) % 217));
	s[5] = (char) (1 + ((17 * i + 129) % 233));
	s[6] = '\0';
}

int blk_num = 0;

int universalhashfunction(char *string, int size, int sum, int *a) {

	char *key = string;
	int m = 0;

	int index = 0;

	while (*key != '\0') {

		m = a[index];
		index++;
		sum += ((m) * ((int) *key));
		key += 1;
	}

	return (sum % size);
}

void set_bit(char *blk, int k) {

	int i = k / 8;
	int pos = k % 8;

	unsigned int flag = 1;

	blk_num++;

	flag = flag << pos;

	blk[i] = blk[i] | flag;

}

int get_bit(char *blk, int k) {
	int i = k / 8;
	int pos = k % 8;

	blk_num++;

	unsigned int flag = 1;

	flag = flag << pos;

	if (blk[i] & flag) {

		return 1;
	} else {
		return 0;
	}

}

bf_t *create_bf() {

	bf_t *block = (bf_t*) calloc(BLK_SZ * 8, sizeof(char));

	int i = 0;

	for (i = 0; i < 8; i++) {

		b[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v0[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v1[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v2[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v3[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v4[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v5[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v6[i] = rand() % MAXP;
	}

	for (i = 0; i < 256; i++) {

		v7[i] = rand() % MAXP;
	}

	return block;
}

void insert_bf(bf_t *block, char *s) {

//	(*bloom).block0[3] = 14;

	int hash = 0;
	int size = 2000000;
	int i = 0;

	blk_num = 0;
//	printf("block first starts %d\n",index);

	for (i = 0; i < 8; i++) {

		if (i == 0) {
			hash = universalhashfunction(s, size, b[i], v0);
		} else if (i == 1) {
			hash = universalhashfunction(s, size, b[i], v1);
		} else if (i == 2) {
			hash = universalhashfunction(s, size, b[i], v2);
		} else if (i == 3) {
			hash = universalhashfunction(s, size, b[i], v3);
		} else if (i == 4) {
			hash = universalhashfunction(s, size, b[i], v4);
		} else if (i == 5) {
			hash = universalhashfunction(s, size, b[i], v5);
		} else if (i == 6) {
			hash = universalhashfunction(s, size, b[i], v6);
		} else if (i == 7) {
			hash = universalhashfunction(s, size, b[i], v7);
		}

		hash = abs(hash);

		if (i == 0) {
			set_bit((*block).block0, hash);
		} else if (i == 1) {
			set_bit((*block).block1, hash);
		} else if (i == 2) {
			set_bit((*block).block2, hash);
		} else if (i == 3) {
			set_bit((*block).block3, hash);
		} else if (i == 4) {
			set_bit((*block).block4, hash);
		} else if (i == 5) {
			set_bit((*block).block5, hash);
		} else if (i == 6) {
			set_bit((*block).block6, hash);
		} else if (i == 7) {
			set_bit((*block).block7, hash);
		}

	}

}

int is_element(bf_t *block, char *s) {

	int result = 0;
	int hash = 0;
	int size = 2000000;

//printf("checking %s\n",s);

	int i = 0;
	int f = 0;

	blk_num = 0;

	for (i = 0; i < 8; i++) {

		if (i == 0) {
			hash = universalhashfunction(s, size, b[i], v0);
		} else if (i == 1) {
			hash = universalhashfunction(s, size, b[i], v1);
		} else if (i == 2) {
			hash = universalhashfunction(s, size, b[i], v2);
		} else if (i == 3) {
			hash = universalhashfunction(s, size, b[i], v3);
		} else if (i == 4) {
			hash = universalhashfunction(s, size, b[i], v4);
		} else if (i == 5) {
			hash = universalhashfunction(s, size, b[i], v5);
		} else if (i == 6) {
			hash = universalhashfunction(s, size, b[i], v6);
		} else if (i == 7) {
			hash = universalhashfunction(s, size, b[i], v7);
		}

		hash = abs(hash);

		if (i == 0) {
			result = get_bit((*block).block0, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 1) {
			result = get_bit((*block).block1, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 2) {
			result = get_bit((*block).block2, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 3) {
			result = get_bit((*block).block3, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 4) {
			result = get_bit((*block).block4, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 5) {
			result = get_bit((*block).block5, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 6) {
			result = get_bit((*block).block6, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		} else if (i == 7) {
			result = get_bit((*block).block7, hash);
			if (result == 0) {
				f++;
			} else if (result == 1) {
			}
		}

	}

	if (f > 0) {
		f = 0;
	} else if (f == 0) {
		f = 1;
	}

	return f;
}

int main() {

	long i, j;
	bf_t * bloom;
	bloom = create_bf();
	printf("Created Filter\n");
	for (i = 0; i < 1450000; i++) {
		char s[8];
		sample_string_A(s, i);
		insert_bf(bloom, s);
	}
	for (i = 0; i < 500000; i++) {
		char s[7];
		sample_string_B(s, i);
		insert_bf(bloom, s);
	}
	for (i = 0; i < 50000; i++) {
		char s[6];
		sample_string_C(s, i);
		insert_bf(bloom, s);
	}
	printf("inserted 2,000,000 strings of length 8,7,6.\n");

	for (i = 0; i < 1450000; i++) {
		char s[8];
		sample_string_A(s, i);
		if (is_element(bloom, s) != 1) {
			printf("found negative error (1)\n");
			exit(0);
		}
	}
	for (i = 0; i < 500000; i++) {
		char s[7];
		sample_string_B(s, i);
		if (is_element(bloom, s) != 1) {
			printf("found negative error (2)\n");
			exit(0);
		}
	}
	for (i = 0; i < 50000; i++) {
		char s[6];
		sample_string_C(s, i);
		if (is_element(bloom, s) != 1) {
			printf("found negative error (3)\n");
			exit(0);
		}
	}
	j = 0;
	for (i = 0; i < 500000; i++) {
		char s[8];
		sample_string_D(s, i);
		if (is_element(bloom, s) != 0)
			j += 1;
	}
	for (i = 0; i < 500000; i++) {
		char s[7];
		sample_string_E(s, i);
		if (is_element(bloom, s) != 0)
			j += 1;
	}
	printf("Found %d positive errors out of 1,000,000 tests.\n", j);
	printf("Positive error rate %f\%.\n", (float) j / 10000.0);

	return 0;
}
