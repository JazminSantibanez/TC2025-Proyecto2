#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> // for close

void execute_client(char *num_to_send) {
  printf("In thread\n");
  char client_request_msg[1024] = {0};
  char server_response[1024] = {0};
  int client_socket;
  struct sockaddr_in server_addr;
  socklen_t addr_size;

  // Create the socket.
  client_socket = socket(PF_INET, SOCK_STREAM, 0);

  // Configure settings of the server address
  // Address family is Internet
  server_addr.sin_family = AF_INET;

  // Set port number, using htons function
  server_addr.sin_port = htons(7799);

  // Set IP address to localhost
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

  // Connect the socket to the server using the address
  addr_size = sizeof server_addr;
  (void)connect(client_socket, (struct sockaddr *)&server_addr, addr_size);

  strcpy(client_request_msg, num_to_send);

  if (send(client_socket, client_request_msg, strlen(client_request_msg), 0) <
      0) {
    printf("Send failed\n");
  }

  // Read the message from the server into the buffer
  if (recv(client_socket, server_response, 1024, 0) < 0) {
    printf("Receive failed\n");
  }
  // Print the received message
  printf("Data received: %s\n", server_response);
  printf("Data length: %lu\n", strlen(server_response));
  close(client_socket);

  double num_to_send_d = strtod(num_to_send, NULL);
  if (fmod(num_to_send_d, 9) != 0 && fmod(num_to_send_d, 7) != 0 &&
      fmod(num_to_send_d, 5) != 0 && fmod(num_to_send_d, 3) == 0) {

    FILE *html_file = fopen("client_index.html", "w+");
    fputs(server_response, html_file);
    fclose(html_file);

#ifdef _WIN32
    system("start client_index.html");
#endif
#ifdef __APPLE__
    system("open client_index.html");
#endif
#ifdef __linux__
    system("sensible-browser client_index.html");
#endif

    sleep(1);
    remove("client_index.html");
  }
}

int main(int argc, char *argv[]) {

  if (argc > 3 || argc < 2) {
    printf(" !! Error: El programa acepta exactamente 1 argumento\n");
    return EXIT_FAILURE;
  }

  char *num_to_send = argv[1];
  execute_client(num_to_send);

  return 0;
}
