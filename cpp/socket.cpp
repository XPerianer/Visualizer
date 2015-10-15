//  Visualizer, a software that allows you to visualize songs live on a led-matrix
//  Copyright (C) 2015 Dominik Meier(XPerianer)
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  E-Mail: hiscore.pressthebutton()hotmail.de

int sockfd; //For socket communication
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
        if (sa->sa_family == AF_INET) {
                return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int socketfunction(int commandPointer[]){
        char buf[MAXDATASIZE];
        int  numbytes;
                        std::string answer;
                        try{ //Be safe if communication fails
                                if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
                                        perror("recv");
                                        //  exit(1);
                                }

                                buf[numbytes] = '\0';

                                for(int i=0; i< numbytes; i++) {
                                        answer += buf[i];
                                }
                                //std::cout << answer << std::endl;
                                //Set everything
                                commandPointer[0] = std::stoi(answer.erase(0,1));
                                if(commandPointer[0] == -1){
                                  return 0;
                                }
                                answer = answer.substr(answer.find_first_of(",") +1);
                                commandPointer[1] = std::stoi(answer);
                                if(commandPointer[1] == -1 || commandPointer[1] == 0 || commandPointer[1] == 1){
                                  return 0;
                                }
                                answer = answer.substr(answer.find_first_of(",")+1);
                                commandPointer[2]  =   std::stoi(answer);
                                answer = answer.substr(answer.find_first_of(",")+1);
                                commandPointer[3] = std::stoi(answer);
                                answer = answer.substr(answer.find_first_of(",")+1);
                                commandPointer[4] = std::stoi(answer);
                                answer = answer.substr(answer.find_first_of(",")+1);
                                commandPointer[5] = std::stoi(answer);
                                //std::cout << commandPointer << std::endl;

                        }
                        catch (...) {
                                std::cout << "Error at Socket reading" << std::endl;
                                usleep(1000000*1);
                        }
                //printf("client: received '%s'\n",buf);

                return 0;
        }



int socketConnection(){
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo("192.168.178.45", PORT, &hints, &servinfo)) != 0) {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
          return 1;
  }





          do {
                  // loop through all the results and connect to the first we can
                  for(p = servinfo; p != NULL; p = p->ai_next) {
                          if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                               p->ai_protocol)) == -1) {
                                  perror("client: socket");
                                  continue;
                          }

                          if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                                  close(sockfd);
                                  perror("client: connect");
                                  continue;
                          }

                          break;
                  }
                  usleep(1000000 * 2);
          } while(p == NULL);
          freeaddrinfo(servinfo); // all done with this structure //We need it later if we want to connect multiple times
          /*if (p == NULL) {
              fprintf(stderr, "client: failed to connect\n");

              return 2;
             }*/

          inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                    s, sizeof s);
          printf("client: connecting to %s\n", s);

          return 0;
}
