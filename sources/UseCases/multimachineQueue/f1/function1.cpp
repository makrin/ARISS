#include "include/CBasefunction.h"

int main(int argc, char *argv[]) {
    int redemarrage = atoi(argv[7]);
    int position = atoi(argv[6]);
    GUI_ARINC_partition("Partition1", position, redemarrage);
    /*if (argc > 3)
            {*/
    for (int count = 1; count < argc; count++) {
        std::cout << "argv " << count << " = " << argv[count] << std::endl;
    }

    std::string emetteur = argv[0]; //NOM DU BINAIRE QUI SERA SON IDENFIANT POUR COMMUNIQUER

    std::cout << "nb arg :" << argc << std::endl;
    std::string arg_samp_sock = argv[1]; //ligne à découper
    std::string arg_Qsock = argv[2];
    std::string arg_Sport = argv[3];
    std::string arg_Qport = argv[4];

    CArgument ARG;
    std::vector<int> vsamp_socket = ARG.split_arg(arg_samp_sock);
    std::vector<int> vqueuing_socket = ARG.split_arg(arg_Qsock);
    std::vector<int> vsamp_port = ARG.split_arg(arg_Sport);
    std::vector<int> vqueuing_port = ARG.split_arg(arg_Qport);


    for (unsigned int i = 0; i < vsamp_socket.size(); i++) {
        std::cout << " use socket :" << vsamp_socket[i] << " for sampling comm" << std::endl;
    }
    for (unsigned int i = 0; i < vqueuing_socket.size(); i++) {
        std::cout << " use socket :" << vqueuing_socket[i] << " for queuing com" << std::endl;
    }
    for (unsigned int i = 0; i < vsamp_port.size(); i++) {
        std::cout << " write in port :" << vsamp_port[i] << "by sampling" << std::endl;
    }
    for (unsigned int i = 0; i < vqueuing_port.size(); i++) {
        std::cout << " write in port :" << vqueuing_port[i] << "by queuing" << std::endl;
    }
    //}	
    //////////////////////
    //INIT comm Queuing //
    //////////////////////
    CQueuing Qservice;

    std::cout << "before loop" << std::endl;


    for (int i = 0; i < 20; i++) {

        //	message=i;
        //	std::ostringstream oss;
        //	oss << message;
        //	std::string result = oss.str();
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::cout << "into the loop" << std::endl;

        char result[256];
        std::string targetHostIP;
        targetHostIP = "casals.laas.fr"; //beware this IP adress is harcoded !!!!
        size_t size = targetHostIP.size() + 1;
        char * machine_name = new char[ size ];
        // copier la chaîne
        strncpy(machine_name, targetHostIP.c_str(), size);
        sprintf(result, "message envoye depuis f1 numero %d", i);
        std::cout << "TEXTE A EMETTRE: " << result << std::endl;
        Qservice.WRITE_QUEUING_MESSAGE(machine_name, vqueuing_port[0], vqueuing_socket[0], emetteur, result);
        std::cout << "emis vers partition 2 : " << machine_name << " " << vqueuing_port[0] << " " << vqueuing_socket[0] << " " << emetteur << " " << result << std::endl;

        std::cout << "queuing message wrote to the port :" << vqueuing_port[0] << std::endl;
        sleep(1);
    }


    for (;;) {

        std::cout << "Dans le boucle for, vqueuing_socket[0] : " << vqueuing_socket[0] << std::endl;
        Qservice.READ_QUEUING_MESSAGE(vqueuing_socket[0]);
        Qservice.Display_Message();
    }




}

