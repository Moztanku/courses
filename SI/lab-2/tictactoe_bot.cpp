/*
    Jacek Zub
    Minmax bot with alpha-beta pruning
*/

/****************************
Maciej Gębala (CC BY-NC 4.0)
Client ver. 0.1
2023-03-30
****************************/
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

#include "board.h"

constexpr int inf = 10000000;
int player;
int opponent;

bool winCheck(const int position[5][5], int p){
    for(int i = 0; i < 28; i++){
        if((position[win[i][0][0]][win[i][0][1]]==p) 
        && (position[win[i][1][0]][win[i][1][1]]==p) 
        && (position[win[i][2][0]][win[i][2][1]]==p) 
        && (position[win[i][3][0]][win[i][3][1]]==p))
            return true;
    }
    return false;
}

bool loseCheck(const int position[5][5], int p){
    for(int i = 0; i < 48; i++){
        if((position[lose[i][0][0]][lose[i][0][1]]==p) 
        && (position[lose[i][1][0]][lose[i][1][1]]==p) 
        && (position[lose[i][2][0]][lose[i][2][1]]==p))
            return true;
    }
    return false;
}

bool drawCheck(const int position[5][5]){
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            if(position[y][x]==0)
                return false;
        }
    }
    return true;
}

std::vector<std::pair<int,int>> getMoves(const int position[5][5], bool max_player){
    std::vector<std::pair<int,int>> moves;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(position[i][j] == 0){
                moves.push_back(std::make_pair(i,j));
            }
        }
    }
    return moves;
}

int columnsBlocked(const int position[5][5], int player){
    int score = 0;
    for(int x = 0; x < 5; x++)
        for(int y = 0; y < 4; y++)
            if(position[y][x] == player){
                score += 1;
                break;
            }
    for(int x = 0; x < 5; x++)
        for(int y = 1; y < 5; y++)
            if(position[y][x] == player){
                score += 1;
                break;
            }
    return score;
}

int rowsBlocked(const int position[5][5], int player){
    int score = 0;
    for(int y = 0; y < 5; y++)
        for(int x = 0; x < 4; x++)
            if(position[y][x] == player){
                score += 1;
                break;
            }
    for(int y = 0; y < 5; y++)
        for(int x = 1; x < 5; x++)
            if(position[y][x] == player){
                score += 1;
                break;
            }
    return score;
}

int diagonalsBlocked(const int position[5][5], int player){
    int score = 0;
    auto check = [&](int start, int d){
        for(int x = start; x < start+4; x++)
            if(position[x+d][x] == player){
                score += 1;
                break;
            }
    };
    check(0, 0);
    check(1, -1);
    check(0, +1);
    check(1, 0);
    auto check2 = [&](int start, int d){
        for(int x = start; x < start+4; x++)
            if(position[4+d-x][x] == player){
                score += 1;
                break;
            }
    };
    check2(0, 0);
    check2(1, +1);
    check2(0, -1);
    check2(1, 0);
    return score;
}

/*
    Funkcja heurystyczna sprawdza najpierw czy gracz wygrał, przegrał lub zremisował.
    Przypisując odpowiednio duże wartości do każdego z tych przypadków.

    Następnie oblicza wartość heurystyczną na podstawie blokowanych linii.
    Każda zablokowana kolumna, rząd lub przekątna długości 4 dodaje +2 do wartości heurystycznej.
    Dodatkowo dodaje +1 za zajęcie środka planszy, ponieważ np. (1,1) blokuje tyle samo linii, jednak
    eksperymentalnie wyszło mi, że zajęcie środka jest lepsze.
*/
int evaluate(const int position[5][5]){
    if(winCheck(position, player) || loseCheck(position, opponent))
        return inf;
    if(winCheck(position, opponent) || loseCheck(position, player))
        return -inf;
    if(drawCheck(position))
        return 2*inf; // Draw is very rare so it's more interesting than win

    int happy = 0;
    int sad = 0;

    if(position[2][2] == player)
        happy += 1;
    else if(position[2][2] == opponent)
        sad += 1;

    happy += 2*(columnsBlocked(position, player) + 
             rowsBlocked(position, player) + 
             diagonalsBlocked(position, player));
    
    sad += 2*(columnsBlocked(position, opponent) +
           rowsBlocked(position, opponent) +
           diagonalsBlocked(position, opponent));

    return happy - sad;
}

bool isTerminal(const int position[5][5], bool max_player){
    int p = max_player ? player : opponent;
    if(winCheck(position, p))
        return true;
    if(loseCheck(position, p))
        return true;
    if(drawCheck(position))
        return true;
    return false;
}

int minmax(const int position[5][5], int depth, bool max_player, int alpha, int beta){
    if(depth == 0 || isTerminal(position, max_player)){
        return evaluate(position);
    }

    if(max_player == true){
        int max_eval = -inf;
        std::vector<std::pair<int,int>> moves = getMoves(position, max_player);
        for(auto move : moves){
            int new_position[5][5];
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    new_position[i][j] = position[i][j];
                }
            }
            new_position[move.first][move.second] = player;
            int eval = minmax(new_position, depth-1, false, alpha, beta);
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha)
                break;
        }
        return max_eval;
    }
    else {
        int min_eval = inf;
        std::vector<std::pair<int,int>> moves = getMoves(position, max_player);
        for(auto move : moves){
            int new_position[5][5];
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    new_position[i][j] = position[i][j];
                }
            }
            new_position[move.first][move.second] = opponent;
            int eval = minmax(new_position, depth-1, true, alpha, beta);
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);
            if(beta <= alpha)
                break;
        }
        return min_eval;
    }
}

std::pair<int,int> minmax(const int position[5][5], int depth){
    int best_score = -inf-1;
    std::pair<int,int> best_move = {-1,-1};
    for (auto move: getMoves(position, true)){
        int new_position[5][5];
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                new_position[i][j] = position[i][j];
            }
        }
        new_position[move.first][move.second] = player;
        int score = minmax(new_position, depth-1, false, -inf, inf);
        if(score > best_score){
            best_score = score;
            best_move = move;
        }
    }
    return best_move;
}

int main(int argc, char *argv[])
{
  int socket_desc;
  struct sockaddr_in server_addr;
  char server_message[16], client_message[16];

  bool end_game;
  int msg, move;

  if( argc!=5 ) {
    printf("Wrong number of arguments\n");
    return -1;
  }

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if( socket_desc<0 ) {
    printf("Unable to create socket\n");
    return -1;
  }

  // Set port and IP the same as server-side
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // Send connection request to server
  if( connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0 ) {
    printf("Unable to connect\n");
    return -1;
  }

  // Receive the server message
  memset(server_message, '\0', sizeof(server_message));
  if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
    printf("Error while receiving server's message\n");
    return -1;
  }
  printf("Server message: %s\n",server_message);

  memset(client_message, '\0', sizeof(client_message));
  strcpy(client_message, argv[3]);
  // Send the message to server
  if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
    printf("Unable to send message\n");
    return -1;
  }

  setBoard(); 
  end_game = false;
  player = atoi(argv[3]);
  opponent = 3-player;
  int depth = atoi(argv[4]);

  while( !end_game ) {
    memset(server_message, '\0', sizeof(server_message));
    if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
      printf("Error while receiving server's message\n");
      return -1;
    }
    printf("Server message: %s\n", server_message);
    msg = atoi(server_message);
    move = msg%100;
    msg = msg/100;
    if( move!=0 ) {
      setMove(move, 3-player);
    }
    if( (msg==0) || (msg==6) ) {
      std::pair<int,int> minmaxResult = minmax(board, depth);
      move = (minmaxResult.first+1)*10 + (minmaxResult.second+1);
      setMove(move, player);
      memset(client_message, '\0', sizeof(client_message));
      sprintf(client_message, "%d", move);
      if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
        printf("Unable to send message\n");
        return -1;
      }
     }
     else {
       end_game = true;
       switch( msg ) {
         case 1 : printf("You won.\n"); break;
         case 2 : printf("You lost.\n"); break;
         case 3 : printf("Draw.\n"); break;
         case 4 : printf("You won. Opponent error.\n"); break;
         case 5 : printf("You lost. Your error.\n"); break;
       }
     }
   }

  // Close socket
  close(socket_desc);

  return 0;
}
