#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define QUANT_NOTEBOOKS 10
#define QUANT_ALUNO 5

int quantNotebookReservado = 6;

struct Notebook {
    int numeroNot;
    int isReservado;
    int isRetirado;
    int isEstragado;
    int raAluno;
    char nomeAluno[50];
    char turno[10];
    char problema[150];
    char data[10];
};

typedef struct 
{
    int raAluno;
    char nome[50];
    int listaNegra;
    int quantReservado;

}Aluno;


void enter();
void inicializarNotebooks(struct Notebook notebook[], int quantNotebooks);
void reservarNotebook(struct Notebook notebook[], int quantNotebooks, Aluno alunoBiopark[],int quantAlunos );
void adicionarReservaAoAluno( Aluno alunoBiopark[], int quantAlunos, int raAlunoReservado);
void loginTI(struct Notebook notebook[], int quantNotebooks);
void loginAdm(struct Notebook notebook[], int quantNotebooks, Aluno alunoBiopark[], int quantAlunos);
void exibirMenuAdm();
void exibeListaNegraMenu();
void verificarDisponibilidade(struct Notebook notebook[], int quantNotebooks);
void mostrarDadosAlunos(struct Notebook notebook[], int quantNotebooks, Aluno alunoBiopark[], int quantAlunos);
void confirmarDevolucao(struct Notebook notebook[], int quantNotebooks);
void registrarDefeito(struct Notebook notebook[], int quantNotebooks);
void listaNegraArea( Aluno alunoBiopark[], int quantAlunos);
void listaNegra( Aluno alunoBiopark[], int quantAlunos);
int  isAlunoInListaNegra(Aluno alunoBiopark[], int quantAlunos, int raAlunoVerifica);
void getNomeAlunoPeloRa(Aluno alunoBiopark[], int quantAlunos, int raAluno, char nome[]);
void adicionarAlunoListaNegra(Aluno alunoBiopark[], int quantAlunos);
void tirarAlunoListaNegra(Aluno alunoBiopark[], int quantAlunos);
void historicoReservas(Aluno alunoBiopark[], int quantAlunos);
void areaRelatorios(Aluno alunoBiopark[], int quantAlunos);
void notebooksComDefeito(struct Notebook notebook[], int quantNotebooks);
void consertoNotebooks(struct Notebook notebook[], int quantNotebooks);
void mostrarQuantidadeReservador();
void exibeOpcoesRelatorios();

int main() {
    setlocale(LC_ALL, "Portuguese");
    struct Notebook notebook[QUANT_NOTEBOOKS];
    Aluno alunoBiopark[QUANT_ALUNO] = {
        {20234561, "caue", 0, 0},
        {20234562, "matheus", 0, 0},
        {20234563, "Viny", 1, 3},
        {20234564, "Alessandra", 1, 2},
        {20234565, "Giovani", 0, 1}
    };
    
    inicializarNotebooks(notebook, QUANT_NOTEBOOKS);
    

    int isAdm;

    do {
        system("cls");
        printf("------- BEM VINDO AO SISTEMA DE RESERVA DE NOTEBOOK -------\n");
        printf("Digite 0 para sair \n");
        printf("Digite 1 para acessar como T.I. \n");
        printf("Digite 2 para acessar como ADM e gerenciar as reservas \n");
        scanf("%d", &isAdm);

        switch (isAdm) {
            case 0:
                printf("\nMuito obrigado por usar o sistema de notebooks\n");
                return 0;
            case 1:
                system("cls");
                loginTI(notebook, QUANT_NOTEBOOKS);
                break;
            case 2:
                system("cls");
                loginAdm(notebook, QUANT_NOTEBOOKS, alunoBiopark, QUANT_ALUNO);
                break;
            default:
                printf("Op√ß√?o inv√?lida. Tente novamente.\n");
        }
    } while (isAdm != 0);

    return 0;
}


void inicializarNotebooks(struct Notebook notebook[], int quantNotebooks) {
    for (int i = 0; i < quantNotebooks; i++) {
        notebook[i].numeroNot = i + 1;
        notebook[i].isReservado = 0;
        notebook[i].isRetirado = 0;
        notebook[i].isEstragado = 0;
        notebook[i].raAluno = 0;
        
        
    }

    notebook[0].isEstragado = 1;
    strcpy(notebook[0].problema, "nao liga mais");

    notebook[3].isReservado = 1;
    notebook[3].raAluno = 20234563;

    notebook[6].isReservado = 1;
    notebook[6].raAluno = 20234562;
}

void loginTI(struct Notebook notebook[], int quantNotebooks) {
    int senhaTI, tentarSenha = 1, login;

    printf("Bem vindo √† √?rea de T.I. do sistema de notebooks \n");

    while (tentarSenha == 1) {
        printf("Informe seu Login: ");
        scanf("%d", &login);
        printf("\n");
        printf("Insira a senha: ");
        scanf("%d", &senhaTI);
        printf("\n");

        if (login == 123456 && senhaTI == 1234567) {
            printf("Login bem sucedido!\n");
            
            int opcao = 0;
            do{
                system("cls");
                printf("Digite 0 para sair.\n");
                printf("Digite 1 ver a lista de Notebooks com defeito.\n");
                printf("Digite 2 para registrar conserto do notebook.\n");
                scanf("%i", &opcao);

                switch (opcao)
                {
                case 0:
                    return;
                    break;
                case 1:
                    notebooksComDefeito(notebook, quantNotebooks);
                    break;
                case 2:
                    consertoNotebooks(notebook, quantNotebooks);
                    break;
                default:
                    printf("Op√ß√?o inv√?lida. Tente novamente.\n");
                    break;
                }
            } while (opcao != 0);
        } else {
            printf("Login ou senha incorretos\n");
            printf("Digite 0 para sair e 1 para tentar novamente\n");
            scanf("%d", &tentarSenha);
        }
    }
}

void exibirMenuAdm() {
    system("cls");
    printf("Digite 1 para fazer a reserva do notebook:\n");
    printf("Digite 2 para verificar quantos notebooks est√?o dispon√≠veis: \n");
    printf("Digite 3 para mostrar os dados dos alunos que pegaram os notebooks: \n");
    printf("Digite 4 para confirmar a devolu√ß√?o de um notebook: \n");
    printf("Digite 5 para registrar notebook com defeito: \n");
    printf("Digite 6 para ver notebooks com defeito:\n");
    printf("Digite 7 para entrar no menu da Lista Negra:\n");
    printf("Digite 8 para visualizar os relatorios:\n");
    printf("Digite 9 para sair: \n");
}

void loginAdm(struct Notebook notebook[], int quantNotebooks,Aluno alunoBiopark[], int quantAlunos) {
    int senhaAdmCorreta, tentarSenhaAdmNovamente, escolhaAdm;
    char loginAdm[10], senhaAdm[10];

    printf("Bem vindo √† √?rea administrativa do sistema de notebooks \n");

    do {
        printf("Por favor, informe seu login: ");
        scanf("%s", loginAdm);
        printf("Por favor, informe sua senha: ");
        scanf("%s", senhaAdm);

        if (strcmp(loginAdm, "admin") == 0 && strcmp(senhaAdm, "123456") == 0) {
            senhaAdmCorreta = 1;
            
            printf("\n------- Login bem-sucedido! -------- \n");

            do {
                exibirMenuAdm();
                scanf("%d", &escolhaAdm);

                switch (escolhaAdm) {
                    case 1:
                        reservarNotebook(notebook, quantNotebooks, alunoBiopark, quantAlunos);
                        break;
                    case 2:
                        verificarDisponibilidade(notebook, quantNotebooks);
                        break;
                    case 3:
                        mostrarDadosAlunos(notebook, quantNotebooks, alunoBiopark, quantAlunos);
                        break;
                    case 4:
                        confirmarDevolucao(notebook, quantNotebooks);
                        break;
                    case 5: 
                        registrarDefeito(notebook, quantNotebooks);
                        break;
                    case 6:
                        notebooksComDefeito(notebook, quantNotebooks);
                        break;
                    case 7:
                        listaNegraArea(alunoBiopark, quantAlunos);
                        break;
                    case 8:
                        areaRelatorios(alunoBiopark, quantAlunos);
                        break;
                    case 9:
                        printf("Saindo da √?rea administrativa...\n");
                        break;   
                    default:
                        printf("Escolha incorreta. Por favor, escolha uma op√ß√?o v√?lida.\n");
                }
            } while (escolhaAdm != 9);

        } else {
            printf("\nLogin ou senha incorretos. Por favor, tente novamente.\n");
            printf("Digite 0 para sair e 1 para tentar novamente: ");
            scanf("%d", &tentarSenhaAdmNovamente);

            if (tentarSenhaAdmNovamente == 0) {
                break;
            }

            senhaAdmCorreta = 0;
        }

    } while (senhaAdmCorreta == 0);
}

void reservarNotebook(struct Notebook notebook[], int quantNotebooks, Aluno alunoBiopark[], int quantAlunos) {
    int VarIsAlunoInListaNegra = 0;

    system("cls");
    printf("Notebooks disponÌveis para reserva:\n");
    for (int i = 0; i < quantNotebooks; i++) {
        if (notebook[i].isReservado == 0 && notebook[i].isEstragado == 0) {
            printf("Notebook %d\n", notebook[i].numeroNot);
        }
    }

    int numeroNot;
    int raAluno;
    char nome[50];
    char turno[10];

    printf("\nDigite o n˙mero do notebook que deseja reservar: ");
    scanf("%d", &numeroNot);

    int notebookEncontrado = 0;
    for (int i = 0; i < quantNotebooks; i++) {
        if (notebook[i].numeroNot == numeroNot && notebook[i].isReservado == 0 && notebook[i].isEstragado == 0) {
            notebookEncontrado = 1;
            break;
        }
    }

    if (!notebookEncontrado) {
        printf("Notebook %d n„o est· disponÌvel para reserva.\n", numeroNot);
        printf("Pressione Enter para voltar...\n");
        getchar();  // Consumir o '\n' deixado pelo ˙ltimo scanf
        getchar();  // Esperar pelo Enter do usu·rio
        return;
    }
    printf("\nDigite o RA do aluno: ");
    scanf("%d", &raAluno);

    VarIsAlunoInListaNegra = isAlunoInListaNegra(alunoBiopark, quantAlunos, raAluno);
    if (VarIsAlunoInListaNegra == 1) {
        printf("\nAluno est· na lista negra. N„o pode reservar o notebook.\n");
    } else {
        getNomeAlunoPeloRa(alunoBiopark, quantAlunos, raAluno, nome);

        notebook[numeroNot - 1].isReservado = 1;
        notebook[numeroNot - 1].raAluno = raAluno;
        strcpy(notebook[numeroNot - 1].nomeAluno, nome);

        int opcao = 1;
        do {
            printf("\nDigite o turno que deseja fazer a reserva (manh„, tarde, noite): ");
            getchar(); // Consumir o '\n' deixado pelo ˙ltimo scanf
            scanf("%[^\n]", turno);

            if (strcmp(turno, "manha") == 0 || strcmp(turno, "tarde") == 0 || strcmp(turno, "noite") == 0) {
                strcpy(notebook[numeroNot - 1].turno, turno);
                break;
            } else {
                printf("\nEscolha um turno v·lido (manh„, tarde, noite).\n");
            }
        } while (opcao != 0);

        printf("\nNotebook %d reservado com sucesso para o aluno %s\n\n", numeroNot, nome);
        adicionarReservaAoAluno(alunoBiopark, quantAlunos, raAluno);
    }
    printf("Pressione Enter para voltar...\n");
    getchar();  // Consumir o '\n' deixado pelo ˙ltimo scanf
    getchar();  // Esperar pelo Enter do usu·rio
}

void getNomeAlunoPeloRa(Aluno alunoBiopark[], int quantAlunos, int raAluno, char nome[]){
  for (int i = 0; i < quantAlunos; i++) {
    if (alunoBiopark[i].raAluno == raAluno) {
       getchar();
       strcpy(nome, alunoBiopark[i].nome);
    }
  }
  return;
}

void verificarDisponibilidade(struct Notebook notebook[], int quantNotebooks) {
    system("cls");
    int contador = 0;
    printf("Funcionalidade: Verificar quantos notebooks est√?o dispon√≠veis\n\n");
    for (int i = 0; i < quantNotebooks; i++) {
        if (notebook[i].isReservado == 0 && notebook[i].isEstragado == 0) {
            printf("Notebook %d dispon√≠vel \n", notebook[i].numeroNot);
            contador++;
        }
    }
    if (contador == 0)
    {
        printf("----Todos os Notebooks j√? Reservados-----\n");
    }
    
    printf("\n");
    enter();
}

void mostrarDadosAlunos(struct Notebook notebook[], int quantNotebooks, Aluno alunoBiopark[], int quantAlunos) {
    
    system("cls");
    char nome[50];
   

    printf("Funcionalidade: Mostrar os dados dos alunos que pegaram os notebooks\n\n");
    for (int i = 0; i < quantNotebooks; i++) {
        if (notebook[i].isReservado == 1) {
            getNomeAlunoPeloRa(alunoBiopark, quantAlunos, notebook[i].raAluno, nome);
            printf("Notebook %d reservado pelo aluno %s de r.a: %d\n", notebook[i].numeroNot, nome, notebook[i].raAluno);
        }
    }
    printf("\n");
    enter();
}

void confirmarDevolucao(struct Notebook notebook[], int quantNotebooks) {
    system("cls");
    printf("Funcionalidade 4: Confirmar a devolu√ß√?o de um notebook\n\n");
    int codigoNotebook, notaFuncionamento;

    printf("Digite o c√?digo do notebook devolvido: ");
    scanf("%d", &codigoNotebook);
    printf("\n");

    if (notebook[codigoNotebook - 1].numeroNot == codigoNotebook && notebook[codigoNotebook - 1].isReservado == 1) {

        printf("Digite uma nota de 0 a 5 para o funcionamento da m√?quina: ");
        scanf("%d", &notaFuncionamento);
        system("cls");

        if (notaFuncionamento < 0 || notaFuncionamento > 5) {
                printf("Por favor, digite uma nota de 0 a 5.\n");
                system("cls");
        }else{ 
                    if (notebook[codigoNotebook - 1].numeroNot == codigoNotebook && notebook[codigoNotebook - 1].isReservado == 1) {
                        printf("Devolu√ß√?o confirmada para o notebook de c√?digo %d com nota de funcionamento %d.\n\n", codigoNotebook, notaFuncionamento);
                        notebook[codigoNotebook - 1].isReservado = 0;
                        notebook[codigoNotebook - 1].raAluno = 0;
                        notebook[codigoNotebook - 1].isRetirado = 0;
                        enter();
                        return;
                    }
        }
    }
    printf("O notebook de c√?digo %d n√?o estava reservado ou n√?o foi encontrado.\n\n", codigoNotebook);
    enter();
    

}

void registrarDefeito(struct Notebook notebook[], int quantNotebooks) {
    system("cls");
    printf("Funcionalidade: Registrar notebook com defeito\n\n");
    
    printf("-----Notebooks-----\n");
    for (int i = 0; i < quantNotebooks; i++) {
        if (notebook[i].isEstragado == 0) {
            printf("Notebook %d\n", notebook[i].numeroNot);
        }
    }
    printf("\n");
    int numeroNot;
        char descricao[150];
        printf("Digite o codigo do notebook com defeito: ");
        scanf("%d", &numeroNot);
    if (numeroNot > 0 && numeroNot < quantNotebooks +1)
    {
        getchar();
        printf("\n");
        printf("Digite qual o problema do notebook:\n");
        scanf("%[^\n]", descricao);
        strcpy(notebook[numeroNot - 1].problema, descricao);
        notebook[numeroNot - 1].isEstragado = 1;
        system("cls");
        printf("O notebook %d foi registrado com defeito\n\n", numeroNot);
        enter();
    }else{
        printf("numero invalido!");
    }
}

void enter(){
    char enter;
    printf("Pressione Enter para voltar...\n");
    while ((getchar()) != '\n'); 
    enter = getchar();
}

void notebooksComDefeito(struct Notebook notebook[], int quantNotebooks){

    system("cls");
    printf("Funcionalidade: Lista de notebooks com defeito.\n\n");
    int opcao;
    printf("---------Notebooks com defeito----------\n");
    for (int i = 0; i < quantNotebooks; i++)
    {
        if (notebook[i].isEstragado == 1)
        {
            printf("Notebook %i\n", i + 1);
        }
    }
    do
    {
        printf("\nDigite 0 para voltar.\n");
        printf("Digite o numero do notebook para detalhar o defeito.\n");
        scanf("%i", &opcao);
        printf("\n");
        if (notebook[opcao - 1].isEstragado == 1)
        {
            system("cls");
            
            printf("Notebook %i\n", opcao);
            printf("\ndefeito:\n%s\n\n", notebook[opcao - 1].problema);
            enter();
            return;
        }else{
            printf("op√ß√?o invalida!!\n");
        }    
        
    } while (opcao != 0);
     
}

void consertoNotebooks(struct Notebook notebook[], int quantNotebooks){
    system("cls");
    printf("Funcionalidade: Registrar conserto do Notebook.\n\n");
    int opcao;
    printf("---------Notebooks com defeito----------\n");
    for (int i = 0; i < quantNotebooks; i++)
    {
        if (notebook[i].isEstragado == 1)
        {
            printf("Notebook %i\n", i + 1);
        }
    }
    
    do
    {
        
        printf("\nDigite o numero do notebook para registrar conserto");
        printf("\nDigite 0 para sair.");
        scanf("%i", &opcao);
        printf("\n");
        if (notebook[opcao - 1].isEstragado == 1)
        {
            system("cls");
            notebook[opcao - 1].isEstragado = 0;
            strcpy (notebook[opcao - 1].problema, "Nenhum");
            printf("Conserto do Notebook %i foi registrado com sucesso.\n\n", opcao);
            enter();
            return;
        }else{
            printf("op√ß√?o invalida!!\n");
        } 
        
    } while (opcao != 0);
    
}

void listaNegraArea( Aluno alunoBiopark[], int quantAlunos){
   int escolhaAdm;

   system("cls");
   printf("Bem vindo √† √?rea da lista negra do sistema de notebooks \n");
   printf("\n");

   

   do {
      exibeListaNegraMenu();
      scanf("%d", &escolhaAdm);

                switch (escolhaAdm) {
                    case 1:
                        listaNegra(alunoBiopark, quantAlunos);
                        break;
                    case 2:
                        tirarAlunoListaNegra(alunoBiopark, quantAlunos);
                        break;
                    case 3:
                        adicionarAlunoListaNegra(alunoBiopark, quantAlunos);
                        break;
                    case 4:
                        printf("Saindo da √?rea da lista negra...\n");
                        break;  
                    default:
                        printf("Escolha incorreta. Por favor, escolha uma op√ß√?o v√?lida.\n");
                }
            } while (escolhaAdm != 4);
}

void exibeListaNegraMenu(){
   printf("Digite 1 para ver Lista Negra:\n");
   printf("Digite 2 para tirar aluno a Lista Negra:\n");
   printf("Digite 3 para adicionar aluno a Lista Negra:\n");
   printf("Digite 4 para sair: \n");
}

void listaNegra( Aluno alunoBiopark[], int quantAlunos){
    system("cls");
    printf("Funcionalidade: Lista Negra\n");
    printf("-----Lista Negra------\n");
    printf("\n");
    for (int i = 0; i < quantAlunos; i++)
    {
        if (alunoBiopark[i].listaNegra == 1)
        {
            printf("Nome:%s   RA:%i \n", alunoBiopark[i].nome, alunoBiopark[i].raAluno);
            printf("-------------------------------------------\n");
        }
        
    }
    
    printf("\n");
    enter();
}

void adicionarAlunoListaNegra(Aluno alunoBiopark[], int quantAlunos){
    int raAluno;
    int tentarNovamente;

    do {
        system("cls");
        printf("Funcionalidade: Adicionar aluno a Lista Negra\n");
        printf("\n");

        printf("Digite o R.A. do aluno a ser adicionado: ");
        scanf("%d", &raAluno);

        int alunoEncontrado = 0;
        for (int i = 0; i < quantAlunos; i++) {
            if (alunoBiopark[i].raAluno == raAluno) {
                alunoBiopark[i].listaNegra = 1;
                printf("Aluno: %s de R.A.: %d adicionado ‡ lista negra\n", alunoBiopark[i].nome, alunoBiopark[i].raAluno);
                printf("-------------------------------------------\n");
                alunoEncontrado = 1;
                break;
            }
        }

        if (!alunoEncontrado) {
            printf("Aluno n„o encontrado.\n");
            printf("Digite 0 para sair e 1 para tentar novamente: ");
            scanf("%d", &tentarNovamente);
        } else {
            tentarNovamente = 0;
        }

    } while (tentarNovamente == 1);

    printf("\n");
    enter();
}

void tirarAlunoListaNegra(Aluno alunoBiopark[], int quantAlunos){
    int raAluno;
    int tentarNovamente;

    do {
        system("cls");
        printf("Funcionalidade: Tirar aluno a Lista Negra\n");
        printf("\n");

        printf("Digite o R.A. do aluno a ser retirado da lista negra: ");
        scanf("%d", &raAluno);

        int alunoEncontrado = 0;
        for (int i = 0; i < quantAlunos; i++) {
            if (alunoBiopark[i].raAluno == raAluno) {
                alunoBiopark[i].listaNegra = 0;
                printf("Aluno: %s de R.A.: %d retirado da lista negra\n", alunoBiopark[i].nome, alunoBiopark[i].raAluno);
                printf("-------------------------------------------\n");
                alunoEncontrado = 1;
                break;
            }
        }

        if (!alunoEncontrado) {
            printf("Aluno n„o encontrado.\n");
            printf("Digite 0 para sair e 1 para tentar novamente: ");
            scanf("%d", &tentarNovamente);
        } else {
            tentarNovamente = 0;
        }

    } while (tentarNovamente == 1);

    printf("\n");
    enter();
}

void mostrarQuantidadeReservador(){
  system("cls");
  printf("Durante esse periodo foram feitas %d reservas de notebooks", quantNotebookReservado);
  printf("\n");
  enter();
}

void adicionarReservaAoAluno( Aluno alunoBiopark[], int quantAlunos, int raAlunoReservado){
  for (int i = 0; i < quantAlunos; i++) {
    if (alunoBiopark[i].raAluno == raAlunoReservado) {
      alunoBiopark[i].quantReservado++;
      break;
    }
  }
  quantNotebookReservado++;
}

void historicoReservas(Aluno alunoBiopark[], int quantAlunos){
  system("cls");
  for (int i = 0; i < quantAlunos; i++) {
    if (alunoBiopark[i].quantReservado > 0) {
       printf("%s ja reservou: %d vez\n", alunoBiopark[i].nome, alunoBiopark[i].quantReservado);
    }
  }
  printf("\n");
  enter();
}

int isAlunoInListaNegra(Aluno alunoBiopark[], int quantAlunos, int raAlunoVerifica){
  int alunoEncontrado = 0;

  for (int i = 0; i < quantAlunos; i++) {
    if(alunoBiopark[i].raAluno == raAlunoVerifica && alunoBiopark[i].listaNegra == 1) {
      alunoEncontrado = 1;
      break;
    }
  }

  return alunoEncontrado;
}


void areaRelatorios(Aluno alunoBiopark[], int quantAlunos){
  int escolhaAdm;

  system("cls");
  printf("Bem vindo √† √?rea de relatorios do sistema de notebooks \n");
  printf("\n");

   do {
      exibeOpcoesRelatorios();
      scanf("%d", &escolhaAdm);

        switch (escolhaAdm) {
                    case 1:
                        mostrarQuantidadeReservador();
                        break;
                    case 2:
                        historicoReservas(alunoBiopark, quantAlunos);
                        break;
                    case 3:
                        printf("Saindo da √?rea da lista negra...\n");
                        break;
                    case 4:
                        break;  
                    default:
                        printf("Escolha incorreta. Por favor, escolha uma op√ß√?o v√?lida.\n");
                }
            } while (escolhaAdm != 3);
}

void exibeOpcoesRelatorios(){
  printf("Digite 1 para ter o relatorio do total de reservas:\n");
	printf("Digite 2 para ter o relatorio de reservas dos alunos: \n");
  printf("Digite 3 para sair: \n");

}