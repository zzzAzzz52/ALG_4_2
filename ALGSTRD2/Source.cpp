#include <iostream>
#include "Tree.h"
#include "List.h"

using namespace std;

class Sifer
{
    class Tree_Builder
    {
        RBTree* rb_tree;
        List* list;
        List* newList1;
        List* newList2;
        Tree_Builder* left;
        Tree_Builder* right;
        string code;

        void partition_problem(int mid)
        {
            //part 1: partition problem solving
            int i = mid + 1;
            int j = list->get_size() + 1;
            ElemL2* Cur;
            bool** A = new bool* [i];
            for (i = 0; i <= mid; i++)
                A[i] = new bool[j];

            for (i = 0; i <= list->get_size(); i++)
                A[0][i] = true;
            for (i = 1; i <= mid; i++)
                A[i][0] = false;

            for (i = 1; i <= mid; i++)
            {
                for (j = 1; j <= list->get_size(); j++)
                {
                    if (A[i][j - 1])
                        A[i][j] = true;
                    else
                    {
                        Cur = list->at(j - 1);
                        if (Cur->key <= i)
                        {
                            if (A[i - Cur->key][j - 1])
                                A[i][j] = true;
                            else
                                A[i][j] = false;
                        }
                        else
                            A[i][j] = false;
                    }
                }
            }
            //part 2: creating sublist using boolean matrix
            i = mid;
            j = list->get_size();
            while (!A[i][j])
                i--;
            while (i > 0)
            {
                while (A[i][j - 1])
                    j--;

                Cur = list->at(j - 1);
                newList1->push_front(Cur->inf, Cur->key);
                i -= Cur->key;
                list->remove(j - 1);
            }

            for (i = 0; i <= mid; i++)
                delete[] A[i];
            delete[] A;
        }

        int get_mid()
        {
            ElemL2* Cur = list->at(0);
            int mid = 0;
            while (Cur)
            {
                mid += Cur->key;
                Cur = Cur->next;
            }
            if (mid % 2 == 0)
                mid /= 2;
            else
            {
                mid /= 2;
                mid++;
            }
            return mid;
        }

        void split()
        {
            newList1 = new List;
            partition_problem(get_mid());
            newList2 = new List(list);

            int L1_sum = 0, L2_sum = 0;
            ElemL2* Cur = newList1->at(0);
            while (Cur)
            {
                L1_sum += Cur->key;
                Cur = Cur->next;
            }
            Cur = newList2->at(0);
            while (Cur)
            {
                L2_sum += Cur->key;
                Cur = Cur->next;
            }

            if (L1_sum >= L2_sum)
            {
                left = new Tree_Builder(newList1, code + '1', rb_tree);
                right = new Tree_Builder(newList2, code + '0', rb_tree);
            }
            else
            {
                left = new Tree_Builder(newList2, code + '1', rb_tree);
                right = new Tree_Builder(newList1, code + '0', rb_tree);
            }
        }

    public:

        Tree_Builder(List* LIST, string CODE, RBTree* RB_TREE)
        {
            rb_tree = RB_TREE;
            code = CODE;

            if (LIST->get_size() == 1)
                rb_tree->insert(code, LIST->at(0)->inf);
            else
            {
                list = new List(LIST);
                split();
            }
        }

        ~Tree_Builder()
        {
            if (list)
            {
                delete list;
                delete newList1;
                delete left;
                delete newList2;
                delete right;
            }
        }
    };

    string input;
    string code;
    string decode;
    Tree_Builder* tree_builder;
    RBTree* rb_tree;
    List* list;

    void decoding()
    {
        string request;
        char symb;
        bool flag = 1;
        for (int i = 0; i < code.length(); i++)
        {
            if (flag)
                request = code[i];
            else
                request += code[i];
            try
            {
                symb = rb_tree->find(request);
                decode += symb;
                flag = 1;
            }
            catch (exception& exception)
            {
                flag = 0;
            }
        }
    }

    void coding()
    {
        for (int i = 0; i < input.length(); i++)
            code += rb_tree->get_key_by_inf(input[i]);
    }

    void create_list()
    {
        ElemL2* Cur;
        int i;
        for (i = 0; i < input.length(); i++)
        {
            Cur = list->find_by_inf(input[i]);
            if (Cur)
                Cur->key += 1;
            else
                list->push_back(input[i], 1);
        }
        if (list->get_size() <= 1)
            throw invalid_argument("");
        list->BubbleSort();
    }

public:

    Sifer(string INPUT)
    {
        input = INPUT;
        list = new List;
        try
        {
            create_list();
        }
        catch (exception& exception)
        {
            throw invalid_argument("Input string must contain more than one symbol\n");
        }
        rb_tree = new RBTree;
        tree_builder = new Tree_Builder(list, "", rb_tree);
        delete tree_builder;
        coding();
        decoding();
    }

    string get_code()
    {
        return code;
    }

    string get_decode()
    {
        return decode;
    }

    void print_freq_table()
    {
        cout << "Frequency table:\n";
        list->print_to_console();
        cout << endl;
    }

    void print_code_table()
    {
        cout << "Code table:\n";
        rb_tree->print();
        cout << endl;
    }

    double get_compression_ratio()
    {
        double a = input.length() * 8;
        double b = code.length();
        return a / b;
    }

    ~Sifer()
    {
        delete list;
        delete rb_tree;
    }
};

int main()
{
    cout << "Enter string\n";
    string input;
    getline(cin, input);
    try
    {
        Sifer S(input);
        cout << "Code: " << S.get_code() << endl;
        cout << "Decode: " << S.get_decode() << endl;
        S.print_code_table();
        S.print_freq_table();
        cout << "Compression ratio: " << S.get_compression_ratio() << endl;
    }
    catch (exception& exception)
    {
        cout << exception.what();
    }
}
