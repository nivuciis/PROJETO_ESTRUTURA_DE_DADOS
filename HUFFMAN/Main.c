#include "Compacta.h"
#include "Descompacta.h"

int main()
{
	char name[100];
	int escolha=0;
	puts("Digite 1 para compactar");
	puts("Digite 2 para descompactar");
		if(scanf("%d",&escolha) == 1)
		{
			getchar();
			puts("Arquivo: ");
			scanf("%[^\n]s",name);
			if(escolha == 1)
				compress(name);
			else if(escolha == 2)
			{
				Decompress_File(name);
			}
		}
	return 0;
}