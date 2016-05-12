//
// Created by pavelgolubev345 on 12.05.16.
//

#include "GoGameLogic.h"

GoGameLogic::GoGameLogic() {
    /* init board */
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            p[i][j] = EMPTY;
    mk = 0;
    uk = 0;
    mik = -1;
    mjk = -1;
    uik = -1;
    ujk = -1;
}

GoGameLogic::~GoGameLogic() {
    int i = 0;
}

//тут все ясно
void GoGameLogic::showboard() {
    int ii;
    printf("   A B C D E F G H J K L M N O P Q R S T\n");
    for (int i = 0; i < 3; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
/* row 16 */
    printf("16");

    for (int j = 0; j < 3; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][3] == 0)
        printf(" +");
    else if (p[3][3] == WHITE)
        printf(" O");
    else if (p[3][3] == BLACK)
        printf(" X");
    else if (p[3][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][9] == EMPTY)
        printf(" +");
    else if (p[3][9] == WHITE)
        printf(" O");
    else if (p[3][9] == BLACK)
        printf(" X");
    else if (p[3][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][15] == EMPTY)
        printf(" +");
    else if (p[3][15] == WHITE)
        printf(" O");
    else if (p[3][15] == BLACK)
        printf(" X");
    else if (p[3][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    printf("16");
    if (umove == 1)
        printf("     Your color: White O\n");
    else if (umove == 2)
        printf("     Your color: Black X\n");
    else
        printf("\n");
/* row 15 to 11 */
    for (int i = 4; i < 9; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        if (i == 4) {
            if (mymove == 1)
                printf("     My color:   White O\n");
            else if (mymove == 2)
                printf("     My color:   Black X\n");
            else
                printf("\n");
        }
        else if (i != 8)
            printf("\n");
        else
            printf("     You have captured %d pieces\n", mk);
    }
/* row 10 */
    printf("10");

    for (int j = 0; j < 3; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][3] == EMPTY)
        printf(" +");
    else if (p[9][3] == WHITE)
        printf(" O");
    else if (p[9][3] == BLACK)
        printf(" X");
    else if (p[9][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][9] == EMPTY)
        printf(" +");
    else if (p[9][9] == WHITE)
        printf(" O");
    else if (p[9][9] == BLACK)
        printf(" X");
    else if (p[9][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][15] == EMPTY)
        printf(" +");
    else if (p[9][15] == WHITE)
        printf(" O");
    else if (p[9][15] == BLACK)
        printf(" X");
    else if (p[9][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    printf("10");
    printf("     I have captured %d pieces\n", uk);
/* row 9 to 5 */
    for (int i = 10; i < 15; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
/* row 4 */
    printf(" 4");

    for (int j = 0; j < 3; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][3] == EMPTY)
        printf(" +");
    else if (p[15][3] == WHITE)
        printf(" O");
    else if (p[15][3] == BLACK)
        printf(" X");
    else if (p[15][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][9] == EMPTY)
        printf(" +");
    else if (p[15][9] == WHITE)
        printf(" O");
    else if (p[15][9] == BLACK)
        printf(" X");
    else if (p[15][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][15] == EMPTY)
        printf(" +");
    else if (p[15][15] == WHITE)
        printf(" O");
    else if (p[15][15] == BLACK)
        printf(" X");
    else if (p[15][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    printf(" 4");
    printf("\n");
/* row 3 to 1 */
    for (int i = 16; i < 19; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
    printf("   A B C D E F G H J K L M N O P Q R S T\n\n");
}

//вывод какой нибудь вспомогательной матрицы для дебажирования
void GoGameLogic::showHelpMat() {
    cout << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            cout << this->p[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "?????????????????????????" << endl;
}


////////////методы подсчета очков игроков на момент окончания игры:
//это методы определения, какой команде пренадлежит пустое поле,
//удаление "мертвых" множеств камней
//и закраска нейтральных полей
//здесь эти методы приведены обратном порядке
//endgame->    //порядок не совсем такой
//


//считает очки и объявляет победителя
gameRes GoGameLogic::endgame(void) {
    //это был тест манагера
    /* BoardManager manager(this);

     int i, j;
     GoGameLogic::getij("b3", &i, &j);
     manager.create_deletedzone(i, j);
     showHelpMat();

     GoGameLogic::getij("p17", &i, &j);
     manager.create_deletedzone(i, j);
     showHelpMat();

     manager.create_neitralzone(10, 10);
     showHelpMat();


     manager.paint_board();
     showHelpMat();*/


//после того как игроки заполнили нейтральные зоны
    //поставить каждому пустому полю в соответствие цвет
    //важно, чтобы перед этой операцией были обнаруженны все нейтральные поля
    //а перед рассчетом нейтральных полей-удалены мертвые поля
    //посчитать очки
    int mtot = 0;
    int utot = 0;
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            if (p[i][j] == 1)
                ++mtot;
            else if (p[i][j] == 2)
                ++utot;
    printf("Your total number of pieces %d\n", utot);
    printf("My total number of pieces %d\n", mtot);
    gameRes res(2);
    res.scores[0] = mtot;
    res.scores[0] = utot;
    return res;
}


////////////методы добавленя фишки которые дергаются в следующем порядке:
//здесь эти методы приведены в обратном порядке
//setChip->getmove->getij(move, i, j)->countlib->suicide->(eval ,count), examboard//порядок не совсем такой

//считает количество свобод клетки и возвращает значение в lib
//рекурентно обходит 8-окрестность точки и и отмечает пройденные
void GoGameLogic::count(int i, int j, int color) {
//пометим текущую как пройденную
    ml[i][j] = EMPTY;
//чекнем север
    if (i != EMPTY) {//если на вход не 0 пришел по строке
        //если сверху пусто и это верхнее поле еще не было учтено(у неучтенных значение 1)
        if ((p[i - 1][j] == EMPTY) && ml[i - 1][j]) {
            ++lib;//увеличивем количество свобод
            ml[i - 1][j] = EMPTY;// учитываем этот кусок
        }
            //если же сверху фишка такого же цвета и это поле неучтено
        else if ((p[i - 1][j] == color) && ml[i - 1][j])
            count(i - 1, j, color);//будем проверять его
    }
//теперь так же чекнем южного соседа
    if (i != 18) {
        if ((p[i + 1][j] == EMPTY) && ml[i + 1][j]) {
            ++lib;
            ml[i + 1][j] = EMPTY;
        }
        else if ((p[i + 1][j] == color) && ml[i + 1][j])
            count(i + 1, j, color);
    }
//западного
    if (j != EMPTY) {
        if ((p[i][j - 1] == EMPTY) && ml[i][j - 1]) {
            ++lib;
            ml[i][j - 1] = EMPTY;
        }
        else if ((p[i][j - 1] == color) && ml[i][j - 1])
            count(i, j - 1, color);
    }
//восточного
    if (j != 18) {
        if ((p[i][j + 1] == EMPTY) && ml[i][j + 1]) {
            ++lib;
            ml[i][j + 1] = EMPTY;
        }
        else if ((p[i][j + 1] == color) && ml[i][j + 1])
            count(i, j + 1, color);
    }
}

//тупо обертка над count, которая сначала инициализирует матрицу ml- которая используется во время
//заполнения матрицы l, в матрице ml отмечаются уже прйденные алгоритмом точки
void GoGameLogic::countlib(int m, int n, int color) {//считает количество свобод кусочка

    //проинициализируем всю вспомогательную матрицу как немаркированную
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            ml[i][j] = 1;
        }
    }
    count(m, n, color);//посчитаем теперь количество свобод кусочка
}

//строит матрицу l-матрицу которая, содержит количество свобод i,j ячейки
void GoGameLogic::eval(int color) {
//оценивает количество свобод каждого закрашенного куска
    //и создает все это в матрицу свобод l[][]
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (p[i][j] == color) {
                lib = 0;
                countlib(i, j, color);
                l[i][j] = lib;
            }
        }
    }
}

//проверка хода на суицидальность
int GoGameLogic::suicide(int i, int j) {
    int m, n, k;

//подсчет кольчества свобод вновь выставленной фишки
    if (currentStep == 1) {
        umove = 1;
        mymove = 2;
    }
    else {
        umove = 2;
        mymove = 1;
    }
    lib = 0;
    countlib(i, j, umove);
    if (lib == 0) {
        /*новый ход-суицидальный, стоит проверить,
         * не убивает ли он множества игрока 2(не получается ли Ko*/
        p[i][j] = umove;//поставим
        eval(mymove);//оценим множества другого игрока после постановки
        k = 0;//счетчик убитых фишек противоположного игрока
        for (m = 0; m < 19; m++)
            for (n = 0; n < 19; n++)
//поле бито, если оно не пусто и у него 0е количество свобод
                if ((p[m][n] == mymove) && !l[m][n]) ++k;
//если нет никакого эффекта или Ко ненастоящий то откатить все назад
        if ((k == 0) || (k == 1 && ((i == uik) && (j == ujk)))) {
            p[i][j] = EMPTY;   /* restore to open */
            return 1;
        }
        else //если все таки провели Ко вернем 0
            return 0;
    }
    else
        return 0;
}

//супер-дупер простая функция, которая парсит простенькую строку с буквой и цифрой хода
int GoGameLogic::getij(char move[], int *i, int *j) {//преобразует строку запроса в координаты i,j
    /*  int k;
      if ((move[0] >= 'A') && (move[0] <= 'H'))
          *j = move[0] - 'A';
      else if ((move[0] >= 'I') && (move[0] <= 'T'))
          *j = move[0] - 'B';
      else if ((move[0] >= 'a') && (move[0] <= 'h'))
          *j = move[0] - 'a';
      else if ((move[0] >= 'j') && (move[0] <= 't'))
          *j = move[0] - 'b';
      else
          return 0;
      k = move[1] - '0';
      if (move[2]) k = k * 10 + move[2] - '0';
      *i = 19 - k;*/
    if ((*i >= 0) && (*i <= 18))
        return 1;
    else
        return 0;
}

//получение, проверка на его валидность(валидный ход==пустое поле&&не в окружение)
bool GoGameLogic::getmove(char move[], int *i, int *j) {
    if (!getij(move, i, j) || (p[*i][*j] != EMPTY) || suicide(*i, *j)) {
        //  cout << "illegal move !" << endl;
        //  printf("your move? ");
        //  scanf("%s", move);
        //  getmove(move, i, j);
        return false;
    }
    else return true;
}

void GoGameLogic::examboard(int color) { /* BLACK or WHITE */
    int i, j, n;

//по вот этой функции строится вспомогательная матрица свобод
    eval(color);

//проинициализируем куски, которые будем удалять
    if (color == 2) {
        mik = -1;
        mjk = -1;
    }
    else {
        uik = -1;
        ujk = -1;
    }
    n = 0; //количество уничтоженных этим ходом

    //удалим все у чего нулевая свобода
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 19; j++) {
            if ((p[i][j] == color) && (l[i][j] == 0)) {
                p[i][j] = EMPTY;
//считаем сколько удалили
                if (color == 2) {
                    mik = i;
                    mjk = j;
                    ++mk;
                }
                else {
                    uik = i;
                    ujk = j;
                    ++uk;
                }
                ++n;  /* increment number of captures on this move */
            }
        }
    }

//если не было КО откатим изменения
    if (color == 2 && n > 1) {
        mik = -1;
        mjk = -1;
    }
    else if (n > 1) {
        uik = -1;
        ujk = -1;
    }
}

bool GoGameLogic::setChipin(char *move, int i, int j, int team) {
    currentStep = team;
    bool moveStatus = getmove(move, &i, &j);
    if (moveStatus == 0) return moveStatus;
    else {
        p[i][j] = team;
        if (team == 1)
            examboard(2);
        else if (team == 2)
            examboard(1);
        return moveStatus;
    }
}

bool GoGameLogic::setChip(int i, int j, int team) {
    // i++;
    //j++;
    char *move = "qwerty";
    bool moveStatus = setChipin(move, i, j, team);
    return moveStatus;
}


/*
void GoGameLogic::showboard() {
    int ii;
    printf("   A B C D E F G H J K L M N O P Q R S T\n");
    for (int i = 0; i < 3; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
    printf("16");

    for (int j = 0; j < 3; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][3] == 0)
        printf(" +");
    else if (p[3][3] == WHITE)
        printf(" O");
    else if (p[3][3] == BLACK)
        printf(" X");
    else if (p[3][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][9] == EMPTY)
        printf(" +");
    else if (p[3][9] == WHITE)
        printf(" O");
    else if (p[3][9] == BLACK)
        printf(" X");
    else if (p[3][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    if (p[3][15] == EMPTY)
        printf(" +");
    else if (p[3][15] == WHITE)
        printf(" O");
    else if (p[3][15] == BLACK)
        printf(" X");
    else if (p[3][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[3][j] == EMPTY)
            printf(" -");
        else if (p[3][j] == WHITE)
            printf(" O");
        else if (p[3][j] == BLACK)
            printf(" X");
        else if (p[3][j] == -1)
            printf(" @");

    printf("16");
    if (umove == 1)
        printf("     Your color: White O\n");
    else if (umove == 2)
        printf("     Your color: Black X\n");
    else
        printf("\n");
    for (int i = 4; i < 9; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        if (i == 4) {
            if (mymove == 1)
                printf("     My color:   White O\n");
            else if (mymove == 2)
                printf("     My color:   Black X\n");
            else
                printf("\n");
        }
        else if (i != 8)
            printf("\n");
        else
            printf("     You have captured %d pieces\n", mk);
    }
    printf("10");

    for (int j = 0; j < 3; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][3] == EMPTY)
        printf(" +");
    else if (p[9][3] == WHITE)
        printf(" O");
    else if (p[9][3] == BLACK)
        printf(" X");
    else if (p[9][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][9] == EMPTY)
        printf(" +");
    else if (p[9][9] == WHITE)
        printf(" O");
    else if (p[9][9] == BLACK)
        printf(" X");
    else if (p[9][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    if (p[9][15] == EMPTY)
        printf(" +");
    else if (p[9][15] == WHITE)
        printf(" O");
    else if (p[9][15] == BLACK)
        printf(" X");
    else if (p[9][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[9][j] == EMPTY)
            printf(" -");
        else if (p[9][j] == WHITE)
            printf(" O");
        else if (p[9][j] == BLACK)
            printf(" X");
        else if (p[9][j] == -1)
            printf(" @");

    printf("10");
    printf("     I have captured %d pieces\n", uk);
    for (int i = 10; i < 15; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
    printf(" 4");

    for (int j = 0; j < 3; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][3] == EMPTY)
        printf(" +");
    else if (p[15][3] == WHITE)
        printf(" O");
    else if (p[15][3] == BLACK)
        printf(" X");
    else if (p[15][3] == -1)
        printf(" @");

    for (int j = 4; j < 9; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][9] == EMPTY)
        printf(" +");
    else if (p[15][9] == WHITE)
        printf(" O");
    else if (p[15][9] == BLACK)
        printf(" X");
    else if (p[15][9] == -1)
        printf(" @");

    for (int j = 10; j < 15; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    if (p[15][15] == EMPTY)
        printf(" +");
    else if (p[15][15] == WHITE)
        printf(" O");
    else if (p[15][15] == BLACK)
        printf(" X");
    else if (p[15][15] == -1)
        printf(" @");

    for (int j = 16; j < 19; j++)
        if (p[15][j] == EMPTY)
            printf(" -");
        else if (p[15][j] == WHITE)
            printf(" O");
        else if (p[15][j] == BLACK)
            printf(" X");
        else if (p[15][j] == -1)
            printf(" @");

    printf(" 4");
    printf("\n");
    for (int i = 16; i < 19; i++) {
        ii = 19 - i;
        printf("%2d", ii);

        for (int j = 0; j < 19; j++)
            if (p[i][j] == EMPTY)
                printf(" -");
            else if (p[i][j] == WHITE)
                printf(" O");
            else if (p[i][j] == BLACK)
                printf(" X");
            else if (p[i][j] == -1)
                printf(" @");

        printf("%2d", ii);
        printf("\n");
    }
    printf("   A B C D E F G H J K L M N O P Q R S T\n\n");
}
*/