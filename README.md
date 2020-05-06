Build and run:  
$ cd build  
$ cmake ..  
$ make  
$ ./tin  

Game server available at: https://github.com/Ficol/TIN

Opis:

Klient domyślnie łączy się z serwerem na adresie 127.0.0.1:8888, można to zmienić modyfikując odpowiednie parametry w pliku common.h. Próbuje również użyć portu 9000 do komunikacji UPD, co również można zmienić w common.h.

Działanie:

Po uruchomieniu, klient próbuje nawiązać połączenie TCP, oraz zająć wskazane gniazdo UDP. Jeżeli obie te akcje zakończę się powodzeniem inicjowana jest gra.

W pierwszej kolejności uruchamiane są dwa wątki:
>TcpHandler:  
* keep_alive_sender - przesyła cyklicznie pakiety "alive" do serwera
* game_state_reader - oczekuje przychodzących od serwera komunikatów na gnieździe TCP (ID, start i stop)

Następnie GameManager zastyga na mutexie Game.ready do momentu kiedy grze zostanie nadane ID. Kiedy to się stanie uruchamiana jest funkcja UdpHandler.setInitPackets(), która nadaje komunikaty zwrotne z ID gry do serwera do momentu, kiedy klient otrzyma pakiet "start" i gra zostanie uruchomiona.

W dalszej kolejności uruchamiane są kolejne trzy wątki:  
> Game: 
* main_thread - co 2 sekundy dodaje do kolejki komunikatów kolejne wielokrotności 100 symulując akcje gracza
> UdpHandler:  
* game_state_reader - oczekuje przychodzących od serwera komunikatów na gnieździe UDP (stan gry)
* commands_sender - przesyła do serwera komunikaty pojawiające się w kolejce gry poprzez gniazdo UDP

Gra kończy się w momencie gdy klient odbierze komunikat "stop" na gnieździe TCP. Wraz z zakończeniem gry program kończy działanie.