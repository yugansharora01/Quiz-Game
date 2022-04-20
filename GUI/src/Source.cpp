//#include <iostream>
//#include <queue>
//
//using namespace std;
//
//class n_back_memory {
//    queue<int>* storage;
//    signed int difficulty;
//    int generator() {
//        srand(time(0));
//        int num1 = (rand() % 20) + 1;
//        int num2 = (rand() % 20) + 1;
//        int sign = (rand() % 4) + 1;
//        if (sign == 1) {
//            cout << num1 << " - " << num2 << "      ";
//            return (num1 - num2);
//        }
//        if (sign == 2) {
//            cout << num1 << " + " << num2 << "      ";
//            return (num1 + num2);
//        }
//        if (sign == 3) {
//            cout << num1 << " * " << num2 << "      ";
//            return (num1 * num2);
//        }
//        if (sign == 4) {
//            cout << num1 << " / " << num2 << "      ";
//            return (num1 / num2);
//        }
//    }
//    void memory(queue<int>* storage, int size) {
//        for (int i = 0; i < size; i++)
//        {
//            storage->push(generator());
//            cout << "WAIT" << endl;
//        }
//        return;
//    }
//public:
//    n_back_memory(signed int difficulty) {
//        this->storage = new queue<int>;
//        this->difficulty = difficulty;
//    }
//    bool runner() {
//        memory(storage, difficulty);
//        int ans = storage->front();
//        while (1)
//        {
//            int input_ans;
//            storage->push(generator());
//            cin >> input_ans;
//            if (input_ans != ans)
//                break;
//            storage->pop();
//            ans = storage->front();
//        }
//        return 0;
//    }
//};
//int main() {
//    signed int difficulty = 0;
//    cout << "Enter difficulty level" << endl;
//    cin >> difficulty;
//    n_back_memory* game = new n_back_memory(difficulty);
//    bool check = game->runner();
//    if (check == 0)
//        cout << "game over";
//    return 0;
//}