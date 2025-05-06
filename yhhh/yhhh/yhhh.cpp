#include <iostream>
#include <iomanip>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <algorithm>
#include <vector>

sql::mysql::MySQL_Driver* driver;
sql::Connection* con;

void connectToDatabase() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "12345");
        con->setSchema("tugas_akhir");
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        exit(1);
    }
};
struct Movie {
    int id;
    std::string judul;
    std::string genre;
    float rating;
    std::string tanggal_rilis;
};


// Sorting by ID
void sortById(std::vector<Movie>& movies, bool ascending = true) {
    if (ascending) {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.id < b.id; });
    }
    else {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.id > b.id; });
    }
}

// Sorting by Title
void sortByTitle(std::vector<Movie>& movies, bool ascending = true) {
    if (ascending) {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.judul < b.judul; });
    }
    else {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.judul > b.judul; });
    }
}

// Sorting by Rating
void sortByRating(std::vector<Movie>& movies, bool ascending = true) {
    if (ascending) {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.rating < b.rating; });
    }
    else {
        std::sort(movies.begin(), movies.end(),
            [](const Movie& a, const Movie& b) { return a.rating > b.rating; });
    }
}
// Binary Search by ID
Movie* binarySearchById(std::vector<Movie>& movies, int targetId) {
    int left = 0;
    int right = movies.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (movies[mid].id == targetId) {
            return &movies[mid];
        }

        if (movies[mid].id < targetId) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return nullptr;
}

// Linear Search by Title (case insensitive)
Movie* searchByTitle(std::vector<Movie>& movies, const std::string& title) {
    for (auto& movie : movies) {
        std::string movieTitleLower = movie.judul;
        std::string searchTitleLower = title;

        // Convert to lowercase for case-insensitive comparison
        std::transform(movieTitleLower.begin(), movieTitleLower.end(),
            movieTitleLower.begin(), ::tolower);
        std::transform(searchTitleLower.begin(), searchTitleLower.end(),
            searchTitleLower.begin(), ::tolower);

        if (movieTitleLower.find(searchTitleLower) != std::string::npos) {
            return &movie;
        }
    }
    return nullptr;
}
// Create
void addMovie(const Movie& movie) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO movies (judul, genre, rating, tanggal_rilis) VALUES (?, ?, ?, ?)");
        pstmt->setString(1, movie.judul);
        pstmt->setString(2, movie.genre);
        pstmt->setDouble(3, movie.rating);
        pstmt->setString(4, movie.tanggal_rilis);
        pstmt->execute();
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
}

// Read all
std::vector<Movie> getAllMovies() {
    std::vector<Movie> movies;
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM movies");

        while (res->next()) {
            Movie movie;
            movie.id = res->getInt("id");
            movie.judul = res->getString("judul");
            movie.genre = res->getString("genre");
            movie.rating = res->getDouble("rating");
            movie.tanggal_rilis = res->getString("tanggal_rilis");
            movies.push_back(movie);
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
    return movies;
}

// Update
void updateMovie(const Movie& movie) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE movies SET judul=?, genre=?, rating=?, tanggal_rilis=? WHERE id=?");
        pstmt->setString(1, movie.judul);
        pstmt->setString(2, movie.genre);
        pstmt->setDouble(3, movie.rating);
        pstmt->setString(4, movie.tanggal_rilis);
        pstmt->setInt(5, movie.id);
        pstmt->execute();
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
}

// Delete
void deleteMovie(int id) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "DELETE FROM movies WHERE id=?");
        pstmt->setInt(1, id);
        pstmt->execute();
        delete pstmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
    }
}

void displayMenu() {
    std::cout << "\nMovie Catalog Database\n";
    std::cout << "1. View All Movies\n";
    std::cout << "2. Add Movie\n";
    std::cout << "3. Search Movie\n";
    std::cout << "4. Update Movie\n";
    std::cout << "5. Delete Movie\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose option: ";
}

void displayMovies(const std::vector<Movie>& movies) {
    std::cout << "\nID  judul                Genre         Rating  Tanggal Rilis\n";
    std::cout << "--------------------------------------------------------\n";
    for (const auto& movie : movies) {
        std::cout << std::left << std::setw(4) << movie.id
            << std::setw(20) << movie.judul.substr(0, 18) + (movie.judul.length() > 18 ? "..." : "")
            << std::setw(13) << movie.genre
            << std::setw(8) << std::fixed << std::setprecision(1) << movie.rating
            << movie.tanggal_rilis << std::endl;
    }
}

void searchMenu() {
    std::cout << "\nSearch Options:\n";
    std::cout << "1. Search by ID\n";
    std::cout << "2. Search by Title\n";
    std::cout << "Choose option: ";
}

void sortMenu() {
    std::cout << "\nSort Options:\n";
    std::cout << "1. Sort by ID (ascending)\n";
    std::cout << "2. Sort by ID (descending)\n";
    std::cout << "3. Sort by Title (A-Z)\n";
    std::cout << "4. Sort by Title (Z-A)\n";
    std::cout << "5. Sort by Rating (highest first)\n";
    std::cout << "6. Sort by Rating (lowest first)\n";
    std::cout << "Choose option: ";
}
int main() {
    connectToDatabase();

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 2: { // Add Movie
            Movie movie;
            std::cout << "Enter title: ";
            std::getline(std::cin, movie.judul);
            std::cout << "Enter genre: ";
            std::getline(std::cin, movie.genre);
            std::cout << "Enter rating: ";
            std::cin >> movie.rating;
            std::cout << "Enter release date (YYYY-MM-DD): ";
            std::cin >> movie.tanggal_rilis;

            addMovie(movie);
            std::cout << "Movie added successfully!\n";
            break;
        }
        case 1: { // View All Movies
            auto movies = getAllMovies();

            int sortChoice;
            sortMenu();
            std::cin >> sortChoice;

            switch (sortChoice) {
            case 1: sortById(movies); break;
            case 2: sortById(movies, false); break;
            case 3: sortByTitle(movies); break;
            case 4: sortByTitle(movies, false); break;
            case 5: sortByRating(movies, false); break;
            case 6: sortByRating(movies); break;
            default: std::cout << "Invalid choice!\n";
            }

            displayMovies(movies);
            break;
        }
        case 3: { // Search Movie
            searchMenu();
            int searchChoice;
            std::cin >> searchChoice;
            std::cin.ignore();

            auto movies = getAllMovies();
            sortById(movies); // Ensure sorted for binary search

            if (searchChoice == 1) {
                int id;
                std::cout << "Enter movie ID: ";
                std::cin >> id;

                Movie* found = binarySearchById(movies, id);
                if (found) {
                    displayMovies({ *found });
                }
                else {
                    std::cout << "Movie not found!\n";
                }
            }
            else if (searchChoice == 2) {
                std::string title;
                std::cout << "Enter movie title: ";
                std::getline(std::cin, title);

                Movie* found = searchByTitle(movies, title);
                if (found) {
                    displayMovies({ *found });
                }
                else {
                    std::cout << "Movie not found!\n";
                }
            }
            else {
                std::cout << "Invalid choice!\n";
            }
            break;
        }
        case 4: { // Update Movie
            int id;
            std::cout << "Enter movie ID to update: ";
            std::cin >> id;
            std::cin.ignore();

            auto movies = getAllMovies();
            Movie* found = binarySearchById(movies, id);

            if (found) {
                Movie updated = *found;
                std::cout << "Current title: " << updated.judul << "\nNew title (press enter to keep): ";
                std::string newTitle;
                std::getline(std::cin, newTitle);
                if (!newTitle.empty()) updated.judul = newTitle;

                // Similar for other fields...

                updateMovie(updated);
                std::cout << "Movie updated successfully!\n";
            }
            else {
                std::cout << "Movie not found!\n";
            }
            break;
        }
        case 5: { // Delete Movie
            int id;
            std::cout << "Enter movie ID to delete: ";
            std::cin >> id;

            deleteMovie(id);
            std::cout << "Movie deleted successfully!\n";
            break;
        }
        case 6:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    delete con;
    return 0;
}