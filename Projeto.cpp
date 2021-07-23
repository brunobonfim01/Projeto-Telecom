#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct cliente
{
char cpf[15];
char nome[50];
float plano;
}s;
void criarplano();
void listarplanos();
void mudarplanos();
void deletar();
void procurar();
char get;
int main()
{	int senha;
	int cpf;
	char escolha;



	system("cls");

	printf("\n\t\t------Sistema de Controle de Planos Telecom------");
	Sleep(2000);
	getch();
    system("cls");
	while (1)
	{
		system("cls");
		printf("\n Digite\n A : para adicionar um novo plano.\n L : para listar os planos.");
		printf("\n M : para modificar os planos.");
		printf("\n S : para procurar planos.");
		printf("\n D : para deletar planos.\n E : para sair.\n");
		escolha=getche();
		escolha=toupper(escolha);
		switch(escolha)
		{
			case 'A':
				criarplano();break;
			case 'L':
				listarplanos();break;
			case 'M':
				mudarplanos();break;
			case 'S':
				procurar();break;
			case 'D':
				deletar();break;
			case 'E':
				system("cls");
				printf("\n\n\t\t\t\tOBRIGADO POR USAR NOSSOS SERVICOS!!");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Dados Incorretos");
				printf("\nAperte qualquer tecla para continuar");
				getch();
		}
	}
}
void criarplano()
{
	FILE *f;
	char teste;
	f=fopen("c:/file.ojs","ab+");
	if(f==0)
	{   f=fopen("c:/file.ojs","wb+");
		system("cls");
		printf("/naperte qualquer tecla para continuar");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Numero do CPF: ");
		scanf("%s",&s.cpf);
		printf("\n Nome: ");
		fflush(stdin);
		scanf("%[^\n]",&s.nome);
		printf("\n Valor do Plano: ");
		scanf("%f",&s.plano);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("O plano foi adicionado com sucesso");
		printf("\n Aperte ESC para sair, ou qualquer outra tecla para adicionar outro plano:");
		teste=getche();
		if(teste==27)
			break;
	}
	fclose(f);
}
void listarplanos()
{
	FILE *f;
	int i;
	if((f=fopen("c:/file.ojs","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Numero do CPF\t\tNome do Cliente\t\t\tValor do Plano\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.cpf,s.nome,s.plano);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void deletar()
{
	FILE *f,*t;
	int i=1;
	char cpf[20];
	if((t=fopen("c:/temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("c:/file.ojs","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Digite o CPF que vai ser deletado: ");
	fflush(stdin);
	scanf("%[^\n]",cpf);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.cpf,cpf)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("cls");
		printf("CPF \"%s\" nao encontrado ):",cpf);
		remove("c:/file.ojs");
		rename("c:/temp.ojs","c:/file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("c:/file.ojs");
	rename("c:/temp.ojs","c:/file.ojs");
	system("cls");
	printf("o CPF %s foi deletado com sucesso!!!!",cpf);
	fclose(f);
	fclose(t);
	getch();
}
void procurar()
{
	FILE *f;
	char cpf[20];
	int flag=1;
	f=fopen("c:/file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Digite o CPF que deseja procurar: ");
	scanf("%s", cpf);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.cpf,cpf)==0)
		{	system("cls");
			printf(" Cliente Encontrado ");
			printf("\n\ncpf: %s\nnome: %s\nplano: Rs.%0.2f\n",s.cpf,s.nome,s.plano);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("CPF não encontrado ):");
		}
	}
	getch();
	fclose(f);
}
void mudarplanos()
{
	FILE *f;
	char cpf[20];
	long int size=sizeof(s);
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Digite o CPF do cliente que você deseja modificar: ");
	scanf("%[^\n]",cpf);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.cpf,cpf)==0)
		{
			system("cls");
			printf("\n Digite o CPF: ");
			scanf("%s",&s.cpf);
			printf("\n Digite o Nome: ");
			fflush(stdin);
			scanf("%[^\n]",&s.nome);
			printf("\n Digite o Valor do Plano: ");
			scanf("%f",&s.plano);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
