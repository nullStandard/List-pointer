#include "list.h"


int main()
{
	// just debuging

	char arr[] = "Hello!";
	char arr1[] = "Hey!";
	char arr2[] = "Hayhai!";
	char arr3[] = "GeneralKenobi!";

	char** head = nullptr;
	StringListRemoveDuplicates(&head);

	StringListInit(&head);

	StringListAdd(head, arr);
	StringListAdd(head, arr);
	StringListAdd(head, arr);

	StringListAdd(head, arr1);
	StringListAdd(head, arr2);
	StringListAdd(head, arr1);
	StringListAdd(head, arr);
	StringListAdd(head, arr);

	StringListAdd(head, arr3);
	StringListAdd(head, arr3);

	/*auto temp = reinterpret_cast<char**>(head[0]);
	auto temp2 = &temp;*/

	cout << StringListSize(head) << endl;
	PrintList(head);
	StringListReplaceInStrings(head, arr, arr1);
	PrintList(head);
	StringListRemoveDuplicates(&head);
	//StringListRemove(&head, arr);
	PrintList(head);

	/*StringListRemove(&head, arr);
	PrintList(head);
	StringListRemove(&head, arr1);
	PrintList(head);
	StringListRemove(&head, arr3);
	PrintList(head);
	StringListAdd(head, arr2);
	PrintList(head);*/

	cout << StringListIndexOf(head, arr2) << endl;

	cout << StringListSize(head) << endl;
	PrintList(head);

	StringListDestroy(&head);

	cout << StringListSize(head) << endl;
	PrintList(head);

	/////////////////////////////////////////////////////////////

	system("pause");
}