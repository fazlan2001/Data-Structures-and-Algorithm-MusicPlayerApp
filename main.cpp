#include <iostream>
#include <string>


using namespace std;

class SongNode
{
public:
    string name;
    SongNode* next;
    SongNode* prev;

    SongNode(const string& songName) : name(songName), next(nullptr), prev(nullptr) {}
};

class Playlist
{
private:
    SongNode* head;

public:
    Playlist() : head(nullptr) {}

    void insertLast(const string& songName)
    {
        SongNode* newNode = new SongNode(songName);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            SongNode* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    void insertFirst(const string& songName)
    {
        SongNode* newNode = new SongNode(songName);

        if (head != nullptr)
        {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
    }

    bool containsSong(const string& songName) const
    {
        SongNode* current = head;
        while (current != nullptr)
        {
            if (current->name == songName)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void displaySongs() const
    {
        SongNode* current = head;
        while (current != nullptr)
        {
            cout << current->name << endl;
            current = current->next;
        }
    }

    SongNode* getHead() const
    {
        return head;
    }

    ~Playlist()
    {
        SongNode* current = head;
        while (current != nullptr)
        {
            SongNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
};

class MusicPlayer
{
private:
    Playlist home;
    Playlist favorites;
    Playlist playlists[3];  // Assuming there are 3 playlists
    int playlistCount;

public:
    MusicPlayer() : playlistCount(0) {}

    void displayMenu()
    {
        cout << "Navigation Pages:\n";
        cout << "1. HOME\n";
        cout << "2. Favorites\n";
        cout << "3. Playlists\n";
        cout << "Enter a number to navigate: ";
    }

    void homePage();
    void addNewSong();
    void listenToSongs();
    void addSongToFavorites();
    void addSongToPlaylist();
    void displayPlaylists();
    void viewPlaylistSongs();
    void playlistPage();
    void createNewPlaylist();
    void playSong();
    void displayFavorites();
    void playSongFromFavorites();
    void playSongFromPlaylist();

    ~MusicPlayer()
    {
        // Destructor if needed
    }
};

void MusicPlayer::homePage()
{
    int choice;
    do
    {
        cout << "Home Page:\n";
        cout << "1. Add a new song\n";
        cout << "2. Listen to songs\n";
        cout << "3. Go to the previous menu\n";
        cout << "Enter a number to proceed: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addNewSong();
            break;
        case 2:
            listenToSongs();
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Please enter a valid number.\n";
        }
    }
    while (choice != 3);
}

void MusicPlayer::addNewSong()
{
    string songName;
    cout << "Enter the name of the new song: ";
    cin.ignore();  // Ignore newline character from previous input
    getline(std::cin, songName);

    home.insertLast(songName);
    cout << "Song added to HOME playlist.\n";
}

void MusicPlayer::listenToSongs()
{
    cout << "Listen to Songs:\n";
    home.displaySongs();

    int choice;
    do
    {
        cout << "1. Play a song\n";
        cout << "2. Add to Favorites\n";
        cout << "3. Add to Playlist\n";
        cout << "4. Go to the previous menu\n";
        cout << "Enter a number to proceed: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            playSong();
            break;
        case 2:
            addSongToFavorites();
            break;
        case 3:
            addSongToPlaylist();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice. Please enter a valid number.\n";
        }
    }
    while (choice != 4);
}

void MusicPlayer::addSongToFavorites()
{
    string songName;
    cout << "Enter the name of the song to add to Favorites: ";
    cin.ignore();  // Ignore newline character from previous input
    getline(cin, songName);

    if (home.containsSong(songName))
    {
        if (!favorites.containsSong(songName))
        {
            favorites.insertFirst(songName);
            cout << "Song added to Favorites playlist.\n";
        }
        else
        {
            cout << "Song is already favorited.\n";
        }
    }
    else
    {
        cout << "Song is not available in the Listen to Songs playlist.\n";
    }
}

void MusicPlayer::addSongToPlaylist()
{
    displayPlaylists();

    int playlistChoice;
    cout << "Enter the number of the playlist to add the song: ";
    cin >> playlistChoice;

    if (playlistChoice >= 1 && playlistChoice <= playlistCount)
    {
        string songName;
        cout << "Enter the name of the song to add to the playlist: ";
        cin.ignore();  // Ignore newline character from previous input
        getline(cin, songName);

        if (home.containsSong(songName))
        {
            if (!playlists[playlistChoice - 1].containsSong(songName))
            {
                playlists[playlistChoice - 1].insertFirst(songName);
                cout << "Song added to Playlist " << playlistChoice << ".\n";
            }
            else
            {
                cout << "Song is already in the playlist.\n";
            }
        }
        else
        {
            cout << "Song is not available in the Listen to Songs playlist.\n";
        }
    }
    else
    {
        cout << "Invalid playlist choice.\n";
    }
}

void MusicPlayer::displayPlaylists()
{
    cout << "Available Playlists:\n";
    for (int i = 0; i < playlistCount; ++i)
    {
        cout << i + 1 << ". Playlist " << i + 1 << "\n";
    }
}

void MusicPlayer::viewPlaylistSongs()
{
    displayPlaylists();

    int playlistChoice;
    cout << "Enter the number of the playlist to view songs: ";
    cin >> playlistChoice;

    if (playlistChoice >= 1 && playlistChoice <= playlistCount)
    {
        cout << "Songs in Playlist " << playlistChoice << ":\n";
        playlists[playlistChoice - 1].displaySongs();
    }
    else
    {
        cout << "Invalid playlist choice.\n";
    }
}

void MusicPlayer::playlistPage()
{
    int choice;
    do
    {
        cout << "Playlists Page:\n";
        cout << "1. Create a new playlist\n";
        cout << "2. Display all playlists\n";
        cout << "3. View songs in a playlist\n";
        cout << "4. Go to the previous menu\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewPlaylist();
            break;
        case 2:
            displayPlaylists();
            break;
        case 3:
            viewPlaylistSongs();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice. Please enter a valid number.\n";
        }
    }
    while (choice != 4);
}

void MusicPlayer::createNewPlaylist()
{
    if (playlistCount < 3)    // Assuming there is a limit of 3 playlists
    {
        playlists[playlistCount].insertLast("Playlist " + std::to_string(playlistCount + 1));
        cout << "Playlist created: Playlist " << playlistCount + 1 << "\n";
        playlistCount++;
    }
    else
    {
        cout << "Maximum number of playlists reached (3).\n";
    }
}

void MusicPlayer::playSong()
{
    int choice;
    Playlist* currentPlaylist = nullptr;
    SongNode* currentSong = nullptr;

    do
    {
        cout << "Play Songs Page:\n";
        cout << "1. Play a song from HOME playlist\n";
        cout << "2. Play a song from Favorites playlist\n";
        cout << "3. Play a song from a Playlist\n";
        cout << "4. Go to the previous menu\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            currentPlaylist = &home;
            break;
        case 2:
            currentPlaylist = &favorites;
            break;
        case 3:
            displayPlaylists();
            int playlistChoice;
            cout << "Enter the number of the playlist to play songs: ";
            cin >> playlistChoice;

            if (playlistChoice >= 1 && playlistChoice <= playlistCount)
            {
                currentPlaylist = &playlists[playlistChoice - 1];
            }
            else
            {
                cout << "Invalid playlist choice.\n";
                continue;
            }
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1)
        {
            string songName;
            cout << "Enter the name of the song to play from HOME playlist: ";
            cin.ignore();  // Ignore newline character from previous input
            getline(cin, songName);

            if (currentPlaylist->containsSong(songName))
            {
                cout << "Now playing: " << songName << " from HOME playlist\n";
                currentSong = currentPlaylist->getHead();
            }
            else
            {
                std::cout << "Song is not in the HOME playlist.\n";
                continue;
            }
        }

        if (choice == 2)
        {
            std::string songName;
            std::cout << "Enter the name of the song to play from Favorites playlist: ";
            std::cin.ignore();  // Ignore newline character from previous input
            std::getline(std::cin, songName);

            if (currentPlaylist->containsSong(songName))
            {
                std::cout << "Now playing: " << songName << " from Favorites playlist\n";
                currentSong = currentPlaylist->getHead();
            }
            else
            {
                std::cout << "Song is not in the Favorites playlist.\n";
                continue;
            }
        }

        if (choice == 4)
        {
            break;
        }

        std::string currentSongName;

        if (currentSong != nullptr)
        {
            std::cout << "Now playing: " << currentSong->name << "\n";
            currentSongName = currentSong->name;
        }
        else
        {
            std::cout << "No songs in the selected playlist.\n";
            continue;
        }

        // Find previous and next songs
        SongNode* previousSong = nullptr;
        SongNode* nextSong = nullptr;

        while (currentSong != nullptr)
        {
            if (currentSong->name == currentSongName)
            {
                if (currentSong->prev != nullptr)
                {
                    previousSong = currentSong->prev;
                }
                if (currentSong->next != nullptr)
                {
                    nextSong = currentSong->next;
                }
                break;
            }
            currentSong = currentSong->next;
        }

        std::cout << "Previous Song: " << (previousSong ? previousSong->name : "null") << "\n";
        std::cout << "Next Song: " << (nextSong ? nextSong->name : "null") << "\n";

    }
    while (choice != 4);
}

void MusicPlayer::displayFavorites()
{
    int choice;
    do
    {
        std::cout << "Favorites Page:\n";
        std::cout << "1. Display all favorited songs\n";
        std::cout << "2. Play a song from Favorites\n";
        std::cout << "3. Go to the previous menu\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            favorites.displaySongs();
            break;
        case 2:
            playSongFromFavorites();
            break;
        case 3:
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid number.\n";
        }
    }
    while (choice != 3);
}

void MusicPlayer::playSongFromFavorites()
{
    std::string songName;
    std::cout << "Enter the name of the song to play from Favorites: ";
    std::cin.ignore();  // Ignore newline character from previous input
    std::getline(std::cin, songName);

    if (favorites.containsSong(songName))
    {
        std::cout << "Now playing: " << songName << " from Favorites\n";
    }
    else
    {
        std::cout << "Song is not in the Favorites playlist.\n";
    }
}

void MusicPlayer::playSongFromPlaylist()
{
    displayPlaylists();

    int playlistChoice;
    std::cout << "Enter the number of the playlist to play songs: ";
    std::cin >> playlistChoice;

    if (playlistChoice >= 1 && playlistChoice <= playlistCount)
    {
        std::string songName;
        std::cout << "Enter the name of the song to play: ";
        std::cin.ignore();  // Ignore newline character from previous input
        std::getline(std::cin, songName);

        if (playlists[playlistChoice - 1].containsSong(songName))
        {
            std::cout << "Now playing: " << songName << " from Playlist " << playlistChoice << "\n";
        }
        else
        {
            std::cout << "Song is not in the selected playlist.\n";
        }
    }
    else
    {
        std::cout << "Invalid playlist choice.\n";
    }
}

int main()
{
    MusicPlayer player;

    int choice;
    do
    {
        player.displayMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            player.homePage();
            break;
        case 2:
            player.displayFavorites();
            break;
        case 3:
            player.playlistPage();
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid number.\n";
        }
    }
    while (choice >= 1 && choice <= 3);

    return 0;
}
