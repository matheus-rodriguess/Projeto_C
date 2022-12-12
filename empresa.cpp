#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

void cadastro();
void consulta();
void consulta_maior();
void alteracao();
void exclusao_logica();
void exclusao_fisica();
void ordenacao_codigo_decrescente();
void ordenacao_codigo_crescente();
int binaria();
void recu_backup();
struct empresa{
    char nome[38];
    int codigo;
    int total_funcionarios;
    float investimentos;
    int e;
} em;

    FILE*fptr;
int main(){
        setlocale(LC_ALL,"Portuguese");
    char op;
    char pos;
    char elem[38];
    int mid;

    do{
        //system("cls");
        printf("\n------------------------------------------------------------------------------------");
        printf("\n Selecione uma das Opçoes abaixo:");
        printf("\n 1_Cadastro");
        printf("\n 2_Consulta");
        printf("\n 3_Consulta empresas com investimento maior que 100 mil");
        printf("\n 4_Alteração");
        printf("\n 5_Exclusao Lógica");
        printf("\n 6_Exclusao Física");
        printf("\n 7_Ordenação pelo código em ordem decrescente");
        printf("\n 8_Busca Binária");
        printf("\n 9_Recuperar Backup");
        printf("\n 0_Sair \n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("opção selecionada: ");
        op = getche();



        switch (op){
            case '1':
                cadastro();
            break;
            case '2':
                consulta();
            break;
            case '3':
                consulta_maior();
            break;
            case '4':
                alteracao();
            break;
             case '5':
                exclusao_logica();
            break;
             case '6':
                exclusao_fisica();
            break;
              case '7':
                ordenacao_codigo_decrescente();
            break;

             case '8':
                ordenacao_codigo_crescente();

                pos = binaria();

                if(pos!=-1){
                    printf("\nA empresa esta na posição [%d]",mid);
                    printf("\nCódigo: %d",em.codigo);
                    printf("\nNome: %s",em.nome);
                    printf("\nTotal de funcionarios: %d",em.total_funcionarios);
                    printf("\nInvestimentos: %2.f",em.investimentos);
                    } else {
                    printf(" Não foi possivel encontrar o nome da empresa!!!! ");
                    }

            break;
             case '9':
                recu_backup();
            break;

            case '0':
                printf("\n Saindo...");
                return -1;
            break;
            default:
                printf("\n opção %c invalida",op);
            break;
        }
    }while(op!='9');
        return (0);
    }


    void cadastro(){
        if((fptr = fopen("empresa.bi","rb+"))==NULL){
            if ((fptr=fopen("empresa.bi","wb"))==NULL){
                printf("\n Erro");
                exit(1);
            }
        }

        printf("\n Nome:");
        setbuf(stdin,NULL);
        scanf("%[^\n]",&em.nome);
        printf("\n Codigo: ");
        scanf("%d",&em.codigo);
        printf("\n Total de Funcionarios: ");
        scanf("%d",&em.total_funcionarios);
        printf("\n Investimentos: ");
        scanf("%f",&em.investimentos);

        em.e = 0;

        fseek(fptr,0,2);
        fwrite(&em,sizeof(em),1,fptr);
        fclose(fptr);
}

    void consulta(){
        if((fptr=fopen("empresa.bi","rb"))==NULL){
            printf("\n Erro");
            exit(1);
        }

    fseek(fptr,0,0);
    while(fread(&em,sizeof(em),1,fptr)){
        if(em.e==0){
            printf("\n Nome = %s",em.nome);
            printf("\n Codigo = %d",em.codigo);
            printf("\n Total de Funcionarios: %d ",em.total_funcionarios);
            printf("\n Investimentos = %.2f",em.investimentos);
        }
    }
    getch();
    fclose(fptr);
    }

    void consulta_maior(){
        if((fptr=fopen("empresa.bi","rb"))==NULL){
            printf("\n Erro");
            exit(1);
        }

    fseek(fptr,0,0);

    while(fread(&em,sizeof(em),1,fptr)){
        if(em.investimentos>100000){
        if(em.e==0){
            printf("\n Nome = %s",em.nome);
            printf("\n Codigo = %d",em.codigo);
            printf("\n Total de Funcionarios: %d ",em.total_funcionarios);
            printf("\n Investimentos = %.2f",em.investimentos);
        }
        }
    }


    getchar();
    fclose(fptr);

    }

    void alteracao(){
        char aux[38];
        if((fptr=fopen("empresa.bi", "rb+"))==NULL){
        printf("\nErro");
        exit(1);
        }
        printf("\n Entre com o nome da empresa a ser encontrado: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]",aux);
        fseek(fptr,0,0);
        while(fread(&em,sizeof(em),1,fptr)){
            if(em.e==0){
                if (strcmp(em.nome,aux)==0){
                    printf("\n Entre com o novo valor de investimento a ser alterado: ");
                    scanf("%f",&em.investimentos);
                    fseek(fptr,ftell(fptr)-sizeof(em),0); /*fseek(fptr,-sizeof(f),1); */
                    fwrite(&em,sizeof(em),1,fptr);
                    fseek(fptr,0,2);
                }
            }
        }
        fclose(fptr);
    }

     void exclusao_logica(){
        char aux[38];
        if((fptr=fopen("empresa.bi", "rb+"))==NULL){
        printf("\nErro");
        exit(1);
        }
        printf("\n Entre com o nome da empresa a ser excluida: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]",aux);
        fseek(fptr,0,0);
        while(fread(&em,sizeof(em),1,fptr)){
            if(em.e==0){
                if(strcmp(em.nome,aux)==0){
                    em.e = 1;
                    fseek(fptr,ftell(fptr)-sizeof(em),0); /*fseek(fptr,-sizeof(f),1); */
                    fwrite(&em,sizeof(em),1,fptr);
                    fseek(fptr,0,2);
                }
            }
        }
        fclose(fptr);
    }

    void exclusao_fisica(){
        FILE*fptraux,*fptrback;
        if((fptr = fopen("empresa.bi","rb"))==NULL){
            printf("\nErro");
            exit(1);
           }
        if ((fptraux = fopen("auxiliar.bi","wb"))==NULL){
            printf("\nErro");
            exit(1);
        }
        if((fptrback = fopen("back.bi","rb+"))==NULL){
            if((fptrback=fopen("back.bi","wb"))==NULL){
                printf("\nErro");
                exit(1);
            }
        }
        fseek(fptr,0,0);
        while(fread(&em,sizeof(em),1,fptr)){
            if(em.e==0){
                fseek(fptraux,0,2);
                fwrite(&em,sizeof(em),1,fptraux);
            }else{
                fseek(fptrback,0,2);
                fwrite(&em,sizeof(em),1,fptrback);
            }

        }
            fclose(fptr);
            fclose(fptraux);
            fclose(fptrback);

            remove("empresa.bi");
            rename("auxiliar.bi","empresa.bi");
    }

     void recu_backup(){
        char nome_empresa[38];

        FILE*fptraux,*fptrback;

        if((fptr = fopen("empresa.bi","rb+"))==NULL){
            if((fptr = fopen("empresa.bi","wb"))==NULL){
                printf("\nErro");
                exit(1);
            }

           }
        if ((fptraux = fopen("auxiliar.bi","wb"))==NULL){
            printf("\nErro");
            exit(1);
        }
        if((fptrback = fopen("back.bi","rb+"))==NULL){
            if((fptrback=fopen("back.bi","wb"))==NULL){
                printf("\nErro");
                exit(1);
            }
        }
        fseek(fptrback,0,0);

        printf("\n Informe o nome da empresa que deseja restaurar: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]",&nome_empresa);

        while(fread(&em,sizeof(em),1,fptrback)){
            if(em.e == 1){
            if(strcmp(em.nome,nome_empresa)==0){
                fseek(fptr,0,2);
                em.e = 0;
                fwrite(&em,sizeof(empresa),1,fptr);
            }
            else{
                fseek(fptraux,0,2);
                fwrite(&em,sizeof(empresa),1,fptraux);
            }
            }

        }
            fclose(fptr);
            fclose(fptraux);
            fclose(fptrback);

            remove("back.bi");
            rename("auxiliar.bi","back.bi");
    }


    void ordenacao_codigo_decrescente(){
        int i,j,n,aux;
        struct empresa em_i,em_j;

        if((fptr=fopen("empresa.bi","rb+"))==NULL){
            printf("\n Erro");
            exit(i);
        }
        fseek(fptr,0,2);
        n = ftell(fptr)/sizeof(em);

        for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
           fseek(fptr,i*sizeof(em),0);
           fread(&em_i,sizeof(em),1,fptr);
           fseek(fptr,j*sizeof(em),0);
           fread(&em_j,sizeof(em),1,fptr);

           if(em_i.codigo < em_j.codigo){
           fseek(fptr,i*sizeof(em),0);
           fwrite(&em_j,sizeof(em),1,fptr);
           fseek(fptr,j*sizeof(em),0);
           fwrite(&em_i,sizeof(em),1,fptr);

            }
            }
        }

            fclose(fptr);
    }
     void ordenacao_codigo_crescente(){
        int i,j,n,aux;
        struct empresa em_i,em_j;

        if((fptr=fopen("empresa.bi","rb+"))==NULL){
            printf("\n Erro");
            exit(i);
        }
        fseek(fptr,0,2);
        n = ftell(fptr)/sizeof(em);

        for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
           fseek(fptr,i*sizeof(em),0);
           fread(&em_i,sizeof(em),1,fptr);
           fseek(fptr,j*sizeof(em),0);
           fread(&em_j,sizeof(em),1,fptr);

           if(em_i.codigo > em_j.codigo){
           fseek(fptr,i*sizeof(em),0);
           fwrite(&em_j,sizeof(em),1,fptr);
           fseek(fptr,j*sizeof(em),0);
           fwrite(&em_i,sizeof(em),1,fptr);

            }
            }
        }

            fclose(fptr);
    }




    int binaria(){
        char elem[38];
        int low, high, mid,n;

        if((fptr=fopen("empresa.bi","rb+"))==NULL){

        if((fptr=fopen("empresa.bi","wb"))==NULL){
            printf("\n Erro");
            exit(1);
            }
        }
        fseek(fptr,0,2);
        n = ftell(fptr)/sizeof(em);

        printf("\n Entre com o nome da empresa a ser encontrado: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]",&elem);


        low = 0;
        high = n-1;

        while(low<=high){
            mid = (low+high)/2;
            fseek(fptr,mid*sizeof(em),0);
            fread(&em,sizeof(em),1,fptr);
            if(strcmp(em.nome,elem)>0){
                high = mid - 1;
            }else if(strcmp(em.nome,elem)<0){
                low = mid + 1;
            }else{
                fclose(fptr);
                return mid;
            }
        }
        fclose(fptr);
        return -1;
    }




