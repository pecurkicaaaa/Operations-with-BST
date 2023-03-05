#include <iostream>
#include <stack>
#include <queue>

using namespace std;


struct cvor {
	struct cvor* desni;
	struct cvor* levi;
	struct cvor* otac;
	int val;
	int visina;
};


struct cvor* umetanje(struct cvor* root, int x,int *maks_visina)
{
	struct cvor* novi = new cvor;
	struct cvor* temp1 = root;
	struct cvor* temp2=root;
	novi->desni = NULL;
	novi->levi = NULL;
	novi->val = x;
	if (root == NULL)
	{
		return novi;;
	}
	while (temp1 != NULL)
	{
		temp2 = temp1;
		if (temp1->val > x)
			temp1 = temp1->levi;
		else
			temp1 = temp1->desni;
	}

	if (x < temp2->val)
	{
		temp2->levi = new cvor;
		temp2->levi = novi;
		novi->visina = temp2->visina + 1;
		if (novi->visina > *maks_visina)
			(*maks_visina)++;
		novi->otac = temp2;
	}
	else if(x>temp2->val)
	{
		temp2->desni = new cvor;
		temp2->desni = novi;
		novi->visina= temp2->visina + 1;
		if (novi->visina > *maks_visina)
			(*maks_visina)++;
		novi->otac = temp2;

	}
	else
	{
		//ponavljajuci cvor
		if (temp2->desni == NULL)
		{
			temp2->desni = new cvor;
			temp2->desni = novi;
			novi->visina = temp2->visina + 1;
			if (novi->visina > *maks_visina)
				(*maks_visina)++;
			novi->otac = temp2;
		}
		else
		{
			temp2 = temp2->desni;
			while (temp2->levi != NULL)
				temp2 = temp2->levi;
			temp2->desni = new cvor;
			temp2->desni = novi;
			novi->visina = temp2->visina + 1;
			if (novi->visina > *maks_visina)
				(*maks_visina)++;
			novi->otac = temp2;
		}

	}




	return root;
}

struct cvor* pronadji(struct cvor* root, int key)
{
	struct cvor* temp1 = root;
	
	while ( temp1 != NULL )
	{
		
		if (temp1->val == key)
		{
			return temp1;
		}
		else if (key > temp1->val)
		{
			temp1 = temp1->desni;
		}
		else
		{
			temp1 = temp1->levi;
		}
	}
	return temp1;

}

int pronadji_brojac(struct cvor* root, int key)
{
	struct cvor* temp1 = root;
	int brojac = 0;
	while (temp1 != NULL)
	{

		if (temp1->val == key)
		{
			brojac++;
			return brojac;
		}
		else if (key > temp1->val)
		{
			brojac++;
			temp1 = temp1->desni;
		}
		else
		{
			brojac++;
			temp1 = temp1->levi;
		}
	}
	return brojac;
}

void delete_bst(struct cvor* root)
{
	if (root == NULL)
		return;
	queue <struct cvor*> q;
	q.push(root);
	struct cvor* pom;
	while (!q.empty())
	{
		pom = q.front();
		q.pop();
		if(pom->levi)
			q.push(pom->levi);
		if(pom->desni)
			q.push(pom->desni);
		delete pom;

	}
	root = NULL;

}



void print(struct cvor* root,int maks_visina)
{
	queue <struct cvor*> q;
	queue <int> qlevel;
	q.push(root);
	qlevel.push(1);
	//q.push(NULL);
	struct cvor* pom;
	int nivo = 0;
	int space_between_nodes = 180;
	int space_left_right = 45;
	int level;
	while (nivo<=maks_visina && !q.empty())
	{
		pom = q.front();
		q.pop();
		level = qlevel.front();
		qlevel.pop();
		if (pom == NULL)
		{
			//cout << "NADJEN";
			if (level != nivo)
			{
				nivo = level;
				cout << "\n\n";
				for (int i = 0; i < space_left_right; i++)
					cout << " ";
				cout << " ";
				space_left_right /= 2;
				space_between_nodes /= 2;
			}
			else
			{
				for (int i = 0; i < space_between_nodes; i++)
					cout << " ";
				cout << " ";
			}
			q.push(NULL);
			q.push(NULL);
			qlevel.push(level + 1);
			qlevel.push(level + 1);
			
		}
		else {

			if (pom->visina != maks_visina)
			{
				q.push(pom->levi);
				q.push(pom->desni);
				qlevel.push(pom->visina + 1);
				qlevel.push(pom->visina + 1);
			}
			
			
			if (pom->visina != nivo)
			{
				//cout << "visina:" << pom->visina;
				cout << "\n\n";
				nivo = pom->visina;
				for (int i = 0; i < space_left_right; i++)
					cout << " ";
				space_left_right /= 2;
				cout << pom->val;
				space_between_nodes /= 2;
				
			}
			else
			{
				for (int j = 0; j < space_between_nodes; j++)
					cout << " ";
				
				cout << pom->val;

			}

			
		}

		
		

	}

	cout << endl << endl;//root = NULL;
	
}

int main()
{
	cout << "IMPLEMENTACIJA BST SA PONAVLJANJEM KLJUCEVA" << endl;
	cout << "\n\n\n";
	cout << "MENI:";
	cout << "\n\n\n";
	cout << "1. Formiranje stabla na osnovu uredjenog niza kljuceva." << endl;
	cout << "2. Umetanje novog kljuca u stablo." << endl;
	cout << "3. Pretraga stabla na zadati kljuc." << endl;
	cout << "4. Formatiran ispis sadrzaja stabla." << endl;
	cout << "5. Evaluacija performansi pretrazivanja u BST." << endl;
	cout << "6. Brisanje stabla iz memorije." << endl;
	cout << "7. Izlazak iz programa.\n\n";

	int choice;
	int k;
	int K[1000];
	struct cvor* root=NULL;
	struct cvor* find;
	struct cvor* next;
	struct cvor* pom;
	double prosecan_broj;
	queue <struct cvor*> q;
	int brojac=0;
	int high, low, mid;
	int maks_visina = 0;
	stack <int> s;
	while (1)
	{
		cout << "Unesite opciju iz menija: ";
		cin>>choice;

		switch (choice)
		{
		case 1:
			cout << "Unesite broj kljuceva: ";
			cin >> k;
			cout << "Unesite kljuceve: ";
			for (int i = 1; i <= k; i++)
				cin >> K[i];

			
			low = 1;
			high = k;
			mid = (high + low) / 2;

			root = new cvor;
			if (root == NULL)
			{
				cout << "Greska u alokaciji.";
				exit(1);
			}
			root->val = K[mid];
			//cout << mid << endl<<endl;
			root->otac = NULL;
			root->visina = 1;
			maks_visina = 1;
			next = root;
			next->levi = NULL;
			next->desni = NULL;
			s.push(mid + 1);
			s.push(high);

			high = mid - 1;
			while (low <= high)
			{
				next->levi = new cvor;
				pom = next;

				next = next->levi;
				mid = (high + low) / 2;
				next->val = K[mid];
				next->otac = pom;
				//cout << mid << endl << endl;
				next->visina = next->otac->visina + 1;
				if (next->visina > maks_visina)
					maks_visina = next->visina;
				next->levi = NULL;
				next->desni = NULL;
				s.push(mid + 1);
				s.push(high);

				high = mid - 1;
			}
			//next->levi = NULL;
			while (!s.empty())
			{
				high = s.top();
				s.pop();
				low = s.top();
				s.pop();

				//cout << high << " " << low << endl;

				if (low <= high)
				{
					//cout << next->val << endl;
					next->desni= new cvor;
					struct cvor* pom = next;
					next = next->desni;
					next->otac = pom;
					mid = (high + low) / 2;
					//cout << "mid je " << mid << endl;
					next->val = K[mid];
					//cout << next->val << endl;
					next->visina = next->otac->visina + 1;
					if (next->visina > maks_visina)
						maks_visina = next->visina;
					next->levi = NULL;
					next->desni = NULL;
					s.push(mid + 1);
					s.push(high);
					high = mid - 1;
					while (low <= high)
					{
						next->levi = new cvor;
						struct cvor* pom = next;

						next = next->levi;
						mid = (high + low) / 2;
						next->val = K[mid];
						
						next->otac = pom;
						next->levi = NULL;
						next->desni = NULL;
						next->visina = next->otac->visina + 1;
						if (next->visina > maks_visina)
							maks_visina = next->visina;
						s.push(mid + 1);
						s.push(high);

						high = mid - 1;
					}
					//next->levi = NULL;
				}
				else
				{
					//next->desni = NULL;
					while (next->otac && next->otac->desni != NULL)
					{
						next = next->otac;
						//cout << next->visina << endl;
					}
					next = next->otac;
				}

			}
		break;


		
		case 2:
			cout << "Unesite kljuc koji zelite da umetnete: ";
			int novi;
			cin >> novi;
			root=umetanje(root, novi,&maks_visina);
			break;

		case 3:
			cout << "Unesite kljuc koji zelite da pretrazite: ";
			int key;
			cin >> key;
			find = pronadji(root, key);
			if (find == NULL)
				cout << "Ne postoji ovaj kljuc.";
			else
			{
				cout << "Pronadjeni kljuc je sin cvora: " << find->otac->val<<endl;
			}
			break;

		case 4:
			/*
			q.push(root);
			struct cvor* pom;
			while (!q.empty())
			{
				pom = q.front();
				q.pop();
				if (pom->levi)
					q.push(pom->levi);
				if (pom->desni)
					q.push(pom->desni);
				cout<< pom->val<<" "<<pom->visina<<endl;

			}*/
			//root = NULL;*/
			//print2D(root);
			//cout << "Maks visina je: " << maks_visina;
			print(root,maks_visina);
			break;

		case 5:
			for (int i = 1; i <= k; i++)
			{
				brojac=brojac+ pronadji_brojac(root, K[i]);

			}
			prosecan_broj = (brojac*1.0) / (k*1.0);
			cout << brojac<<" "<<k<<endl;
			cout << "Prosecan broj koraka je: "<<prosecan_broj<<endl;
			break;


		case 6:
			delete_bst(root);
			break;

		case 7: 
			break;
        }
		if (choice == 7)
		{
			cout << "Dovidjenja" << endl;
			break;
		}

	}




}