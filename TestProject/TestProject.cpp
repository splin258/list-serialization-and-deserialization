// TestProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/**
* @note формат записи списка в файле: ${N}(${Data}~${Index})[]
* @exampe 5ads~-1presd~2aweq~-1zxc~0sddf~-1
* @param N - кол-во элементов в списке
* @param Str - Data
* @param Index - Номер элемента списка на котроый есть ссылка 
* @note Index должен иметь значения от 0 до N или -1 если нет ссылки на рандомный элемент списка
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>


class ListNode
{
public:
    ListNode* Prev = nullptr;
    ListNode* Next = nullptr;
    ListNode* Rand = nullptr;
    std::string Data = "";

};

class ListRand
{
public:
    ListNode* Head = nullptr;
    ListNode* Tail = nullptr;
    int Count = 0;

    void Serialize(std::ostream& Stream);

    void Deserialize(std::istream& Stream);
};

struct SRandNode
{
    ListNode* Node = nullptr;
    int PosRand = 0;
};

void ListRand::Serialize(std::ostream& Stream)
{
    Stream << Count;
    std::unordered_map<ListNode*, int> ListSave;
    ListNode* Node = Head;

    if (!Head)
    {
        std::cerr << "The list is empty" << std::endl;
        return;
    }

    int PositionInList = 0;
    while (Node)
    {
        ListSave.insert(std::make_pair(Node, PositionInList));
        Node = Node->Next;
        ++PositionInList;
    }

    Node = Head;
    while (Node)
    {
        Stream << Node->Data << '~';
        if (Node->Rand)
        {
            Stream << ListSave[Node->Rand];
        }
        else
        {
            Stream << "-1";
        }

        Node = Node->Next;
    }

    if (Stream.fail() || Stream.bad())
    {
        std::cerr << "Fail file reading" << std::endl;
    }

    return;
}

void ListRand::Deserialize(std::istream& Stream)
{
    Stream >> Count;
    std::cout << "size: " << Count << std::endl;

    ListNode* CurrentNode = nullptr;

    std::vector<SRandNode> NodeWithLink;
    std::unordered_map<int, ListNode*> ListTemp;

    int SizeList = Count;
    int PositionInList = 0;
    while (SizeList > 0 && !Stream.eof() && !Stream.bad() && !Stream.fail())
    {
        std::string Data;

        std::getline(Stream, Data, '~');
        int Rand;
        Stream >> Rand;

        std::cout << "Data: " << Data << " Rand: " << Rand << std::endl;

        ListNode* Node = new ListNode;
        Node->Data = Data;

        if (Head == nullptr)
        {
            Head = CurrentNode = Tail = Node;
        }
        else
        {
            CurrentNode->Next = Node;
            Node->Prev = CurrentNode;
            Tail = CurrentNode = Node;
        }

        if (Rand != -1)
        {
            SRandNode SRandomNode;
            SRandomNode.Node = CurrentNode;
            SRandomNode.PosRand = Rand;
            NodeWithLink.push_back(SRandomNode);
        }

        ListTemp[PositionInList] = CurrentNode;

        --SizeList;
        ++PositionInList;
    }

    if (!NodeWithLink.empty())
    {
        for (const auto& r : NodeWithLink)
        {
            r.Node->Rand = ListTemp[r.PosRand];
        }
    }

    if (Stream.bad() || Stream.fail())
    {
        std::cerr << "Fail file reading" << std::endl;
    }
}


void clear(ListNode*& Head, ListNode*& Tail, int& Count)
{
    ListNode* node = Head;
    while (node)
    {
        ListNode* temp = node->Next;
        delete node;
        node = temp;
    }

    Head = Tail = nullptr;
    Count = 0;
}

int main()
{
    const std::string FileName = "D:\\List.txt";
    ListRand* List = new ListRand;

    while (1)
    {
        int var;
        std::cout << "1) Serialize" <<std::endl << "2) Deserialize" << std::endl
            << "3) Exit" << std::endl;
        std::cin >> var; 
        switch (var)
        {
            case 1: 
            {
                const std::string FileName2 = "D:\\List2.txt";
                std::fstream Stream(FileName2, std::ios_base::out);
                if (Stream.is_open())
                {
                    List->Serialize(Stream);
                }
                else
                {
                    std::cerr << "Error file open!" << std::endl
                        << "Check file name or file location." << std::endl;
                    return 0;
                }
                Stream.close();

            }
            break;
            case 2:
            {
                std::fstream Stream (FileName, std::ios_base::in);
                if (Stream.is_open())
                {
                    List->Deserialize(Stream);
                }
                else 
                {
                    std::cerr << "Error file open!" << std::endl
                        << "Check file name or file location." << std::endl;
                    return 0;
                }
                Stream.close();
           
            }
            break;
            case 3:
            {
                return 0;
            }
            break;
            default:
            {
                std::cerr << "Mistake" << std::endl
                    << "Repeat the command for example: 2" << std::endl;
            }
            break;
        }
    }
    clear(List->Head, List->Tail, List->Count);
    delete List;
    return 0;
    
}
