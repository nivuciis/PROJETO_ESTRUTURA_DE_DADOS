/* Este programa realiza testes unitários nas funções importantes do projeto 
 * compilar e rodar para obter informações sobre o correto funcionamento das
 * funções. É necessário possuir o CUnit instalado e compilar passando o argu-
 * mento -lcunit.
 */

#include <stdio.h>
#include "Descompacta.h" 
#include "Compacta.h" 
#include <CUnit/CUnit.h> 
#include <CUnit/Basic.h> 

#define TESTING_FILE (fopen("test.txt", "a")) // arquivo usado para testar funcoes



/******************** Funções da biblioteca Descompacta.h **********************/
void test_trash_size(void);

void test_tree_size(void);

void test_huffman_tree(void);

void test_extract(void);

void test_get_file_size(void);

void test_decompress(void);

void test_print_ht(void);

void test_decompress_file(void);

/* *************Funções da biblioteca Compactar.h**************** */
void test_create_header(void);

void test_set(void);

void test_compress(void);
/* ************************************************************************ */


int main(void) {
	
	CU_pSuite decompress_suite = NULL;
	CU_pSuite compress_suite = NULL;

    /* inicializando CUnit */
	if (CU_initialize_registry() != CUE_SUCCESS){
		fprintf(stderr, "Não foi possível inicializar o CUnit.\n");
		return (CU_get_error());
	}

	decompress_suite = CU_add_suite("heap", NULL, NULL);
	if (decompress_suite == NULL) {
		CU_cleanup_registry();
		fprintf(stderr, "Não foi possível adicionar a suite de testes decompress ");
		fprintf(stderr, "suite ao CUnit.\n");
		return (CU_get_error());
	}

	/* criar suite para os testes de funções do programa AVL vs BST */
	compress_suite = CU_add_suite("hash suite", NULL, NULL);
	if (compress_suite == NULL) {
		CU_cleanup_registry();
		fprintf(stderr, "Não foi possível adicionar a suite de testes ");
		fprintf(stderr, "compress suite ao CUnit.\n");
		return (CU_get_error());
	}

    /* adicionando testes às suites */
	if ((CU_add_test(decompress_suite, "test of trash_size()", test_trash_size) == NULL)
		|| (CU_add_test(decompress_suite, "test of tree_size()", test_tree_size) == NULL)
		|| (CU_add_test(decompress_suite, "test of huffman_tree()", test_huffman_tree) == NULL)
		|| (CU_add_test(decompress_suite, "test of extract()", test_extract) == NULL)
		|| (CU_add_test(decompress_suite, "test of get_file_size()", test_get_file_size) == NULL)
		|| (CU_add_test(decompress_suite, "test of decompress()", test_decompress) == NULL)
		|| (CU_add_test(decompress_suite, "test of print_ht()", test_print_ht) == NULL)
		|| (CU_add_test(decompress_suite, "test of decompress_file()", test_decompress_file) == NULL)
		|| (CU_add_test(compress_suite, "test of create_header()", test_create_header) == NULL)
		|| (CU_add_test(compress_suite, "test of set()", test_set) == NULL)
		|| (CU_add_test(compress_suite, "test of compress()", test_compress) == NULL))
	{
		CU_cleanup_registry();
		fprintf(stderr, "Não foi possível adicionar um teste a uma suite.");
		return (CU_get_error());
	}

    /* rodando testes com a interface básica */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return (CU_get_error());
}


/* testa a função Trash_size usando CUnit */
void test_trash_size(void) {
    rewind(TESTING_FILE);
    int trash_size = fgetc(TESTING_FILE) >> 5;
    CU_ASSERT(Trash_Size(TESTING_FILE) 
                == trash_size);
}

/* testa a função tree_size usando CUnit */
void test_tree_size(void) {
    rewind(TESTING_FILE);
    unsigned short first_byte = fgetc(TESTING_FILE) << 11;
    first_byte = first_byte>>3;
    unsigned short second_byte = fgetc(TESTING_FILE);
    first_byte |= second_byte;
    CU_ASSERT(Tree_Size(TESTING_FILE) == first_byte);
}

/* testa a função Huffman_tree usando CUnit */
void test_huffman_tree(void) {
    huffmanTree *new_tree_node = createNODE(&, 0);
    CU_ASSERT(Huffman_Tree(TESTING_FILE, '//') == NULL); /* binary_tree *deve* ser NULL */
}

