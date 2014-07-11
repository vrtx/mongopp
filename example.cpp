#include <iostream>
#include <mongopp.hpp>

using namespace std;
using namespace mongo;

int main(int argc, char *argv[]) {

    // connect and get the database and collection
    Client client("mongodb://127.0.0.1:27017");
    Database database = client.getDatabase("test_db");
    database.drop();
    Collection collection = client.getCollection("test_db", "test_collection");

    // inset some sample documents
    for (int64_t i = 0; i < 10; i++) {
        Document profile;
        profile["name"] = "Ben";
        profile["age"] = 33;
        profile["favoriateNumber"] = rand() % 1000;
        profile["identifier"] = i;
        collection.insert(profile);
    }

    Cursor cursor = collection.find();

    while (cursor.hasNext())
        cout << cursor.next() << endl;

    return 0;
}