/*#include "List.h"

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

    if(!Head) 
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
*/