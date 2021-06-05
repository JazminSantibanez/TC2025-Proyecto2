#include "server_functions.h"
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h> // for close

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void socket_thread(int client_socket) {
  char client_message[2048] = {0};
  char server_response[1024] = {0};
  int new_socket = client_socket;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char time[1024] = {0};
  sprintf(time, "Time: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  recv(new_socket, client_message, 2048, 0);

  double received_num = strtod(client_message, NULL);

  // Send message to the client socket
  pthread_mutex_lock(&lock);

  // TODO(GOD): create response
  if (fmod(received_num, 9) == 0) {
    point response = regresion(received_num);

    char regresion_formula[1024];
    sprintf(regresion_formula, "y_hat = %f + %fx\n", response.b0, response.b1);

    strcpy(server_response, time);
    strcat(server_response, regresion_formula);
  } else if (fmod(received_num, 7) == 0) {
    char pi_str[1024] = {0};
    sprintf(pi_str, "%f", calculate_pi());

    strcpy(server_response, time);
    strcat(server_response, pi_str);
  } else if (fmod(received_num, 5) == 0) {
    char mat_sum[1024] = {0};
    sprintf(mat_sum, "%d", total_sum(received_num));

    strcpy(server_response, time);
    strcat(server_response, mat_sum);
  } else if (fmod(received_num, 3) == 0) {
    char *html = get_html();

    strcpy(server_response, time);
    strcat(server_response, html);
  } else if (fmod(received_num, 2) == 0) {
    char closest_prime[1024] = {0};
    sprintf(closest_prime, "%d", nearest_prime(received_num));

    strcpy(server_response, time);
    strcat(server_response, closest_prime);
  }

  pthread_mutex_unlock(&lock);
  sleep(1);
  send(new_socket, server_response, strlen(server_response), 0);
  printf("Exit socket_thread. Length was: %lu\n", strlen(server_response));
  close(new_socket);
}

int main() {
  int server_socket, new_socket;
  struct sockaddr_in server_addr;
  struct sockaddr_storage server_storage;
  socklen_t addr_size;
  pid_t pid[50];

  // Create the socket.
  server_socket = socket(PF_INET, SOCK_STREAM, 0);

  // Configure settings of the server address struct
  // Address family = Internet
  server_addr.sin_family = AF_INET;

  // Set port number, using htons function to use proper byte order
  server_addr.sin_port = htons(7799);

  // Set IP address to localhost
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Set all bits of the padding field to 0
  memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

  // Bind the address struct to the socket
  (void)bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr));

  // Listen on the socket, with 50 max connection requests queued
  if (listen(server_socket, 50) == 0)
    printf("Listening\n");
  else
    printf("Error\n");

  int i = 0;
  while (1) {
    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof server_storage;
    new_socket =
        accept(server_socket, (struct sockaddr *)&server_storage, &addr_size);
    int pid_c = 0;
    if ((pid_c = fork()) == 0) {
      socket_thread(new_socket);
    } else {
      pid[i++] = pid_c;
      if (i >= 49) {
        i = 0;
        while (i < 50)
          waitpid(pid[i++], NULL, 0);
        i = 0;
      }
    }
  }
  return 0;
}
