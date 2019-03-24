#include <iostream>
#include "mylib.h"
#include "duykhanh_scl.h"

using namespace std;


typedef struct NODE
{
	int data;
	NODE *pLeft;
	NODE *pRight;
};

typedef NODE* TREE;


NODE *CreateNode(int x)
{
	NODE *q = new NODE;
	if(q == NULL)
	{
		cout<<"Khong Du Vung Nho De Cap Phat"<<endl;
		return NULL;
	}
	
	q->data = x;
	q->pLeft = NULL;
	q->pRight = NULL;
	return q;
}




/*-------SUPPORT DUYET CAY THEO MUC-------*/
struct node{
	TREE diachi;
	struct node *next;
};
typedef struct node Node_queue;

struct queue{
	Node_queue *Front;
	Node_queue *Rear;
};
typedef struct queue Queue;


void Init_Queue(Queue &q)
{
	q.Front = q.Rear = NULL;
}

void InSert_queue(Queue &q , TREE x)
{
	Node_queue *p = new Node_queue;
	p->diachi = x;
	p->next = NULL;
	if(q.Front == NULL)
	{
		q.Front = p;
	}
	else
	{
		q.Rear->next = p;
		q.Rear = p;
	}
}


TREE Delete_queue(Queue &q)
{
	Node_queue *p;
	TREE x;
	if(q.Front == NULL)
	{
		return NULL;
	}
	else
	{
		p = q.Front;
		x = p->diachi;
		q.Front = p->next;
		delete p;
		return x;
	}
}


void DuyetCaytheoMuc(TREE root , Queue &q)
{
	TREE p;
	q.Front = NULL;
	q.Rear = NULL;
	if(root != NULL)
	InSert_queue(q,root);
	while(q.Front != NULL)
	{
		p = Delete_queue(q);
		cout<<p->data<<"   ";
		if(p->pLeft != NULL)
		{
			InSert_queue(q,p->pLeft);
		}
		if(p->pRight != NULL)
		{
			InSert_queue(q,p->pRight);
		}
	}
}



void InitTree(TREE &t)
{
	t = NULL;
}


bool IsTreeEmpty(TREE t)
{
	if(t == NULL)
	{
		return true;
	}
	return false;
}



bool AddNode(TREE &t, int x)//Khi them Nod vao BST phai dam bao khong co phan tu trung nhau
{
	if(t == NULL)//NEU CAU RONG
	{
		NODE *q  = CreateNode(x);
		t = q;//gan Node Vua Khoi Tao Cho Cay - Node dau tien chinh la Node Goc (Root)
		return true;
	}
	
	else//cay da ton tai phan tu nay
	{
		if(x == t->data)//phan tu dua vao BST da ton tai trong BST
		{
			return false;
		}
		//cac thu tuc de quy khong co toan tu return
		else if(x > t->data)
		{
			AddNode(t->pRight, x);
		}
		else if(x < t->data)
		{
			AddNode(t->pLeft, x);
		}
	}
}



void Duyet_LNR(TREE t)
{
	if(t != NULL)
	{
		Duyet_LNR(t->pLeft);//duyet toi qua trai cuoi cung
		cout << t->data <<" ";
		Duyet_LNR(t->pRight);
	}
}


bool SearchNodeBST(TREE t, int x)
{
	if(t != NULL)
	{
		if(x < t->data)
		{
			SearchNodeBST(t->pLeft,x);
		}
		else if(x > t->data)
		{
			SearchNodeBST(t->pRight,x);
		}
		else
		{
			return true;//x == t->data
		}
	}
}


/////////SEARCH BST KHONG SU DUNG DE QUY//////////////
bool searchNodeBST(TREE t,  int x)
{ 
    NODE* p = t;//NODE *p
    while (p != NULL) 
    {
        if(x == p->data)
        {
            return true;
		}
        else if(x < p->data) 
        p = p->pLeft;
        else
        p = p->pRight;
      }
      return false;
}



void DemSoLuongSoNguyenTo(TREE t, int &demSNT)
{
	if(t != NULL)
	{
		DemSoLuongSoNguyenTo(t->pLeft,demSNT);
		if(KiemTraSoNguyenTo(t->data) == true)
		{
			demSNT++;
		}
		DemSoLuongSoNguyenTo(t->pRight,demSNT);
	}
}


void TimMaxTrongBST(TREE t, int &max)
{
	if(t != NULL)
	{
		TimMaxTrongBST(t->pLeft, max);
		if(t->data > max)
		{
			max = t->data;
		}
		TimMaxTrongBST(t->pRight, max);
	}
}



void SoNodeLaCuaBST(TREE t, int &NodeLa)
{
	if(t != NULL)
	{
		SoNodeLaCuaBST(t->pLeft, NodeLa);
		if(t->pLeft == NULL && t->pRight == NULL)
		{
			NodeLa++;
			cout<<"Node La: "<<t->data<<endl;
		}
		SoNodeLaCuaBST(t->pRight, NodeLa);
	}
}



void SoNodeCoMotCayCon(TREE t, int &Node1SubTree)
{
	if(t != NULL)
	{
		SoNodeCoMotCayCon(t->pLeft, Node1SubTree);
		if((t->pLeft != NULL && t->pRight == NULL) || (t->pLeft == NULL && t->pRight != NULL))
		{
			Node1SubTree++;
			cout<<"Node Co 1 NodeSub: "<<t->data<<endl;
		}
		SoNodeCoMotCayCon(t->pRight, Node1SubTree);
	}
}



void SoNodeCoHaiCayCon(TREE t, int &Node2SubTree)
{
	if(t != NULL)
	{
		SoNodeCoHaiCayCon(t->pLeft, Node2SubTree);
		if(t->pLeft != NULL && t->pRight != NULL)
		{
			Node2SubTree++;
			cout<<"Node Co 2 NodeSub: "<<t->data<<endl;
		}
		SoNodeCoHaiCayCon(t->pRight, Node2SubTree);
	}
}


int DemNodeChiCoMotCayConPhai(TREE t)
{
	if(t != NULL)
	{
		int ax = DemNodeChiCoMotCayConPhai(t->pLeft) + DemNodeChiCoMotCayConPhai(t->pRight);
		if(t->pLeft == NULL && t->pRight != NULL)
		{
			cout<<"Node Chi Co 1 Cay Con Phai: "<<t->data<<endl;
			return ax+=1;
		}
		else
		{
			return ax;
		}
	}
	else
	 return 0;
}


int DemNodeChiCoMotCayConTrai(TREE t)
{
	if(t != NULL)
	{
		int b = DemNodeChiCoMotCayConTrai(t->pLeft) + DemNodeChiCoMotCayConTrai(t->pRight);
		if(t->pLeft != NULL && t->pRight == NULL)
		{
			cout<<"Node Chi Co 1 Cay Con Trai: "<<t->data<<endl;
			return b+=1;
		}
		else
		{
			return b;
		}
	}
	else
	 return 0;
}


void TongSoNodeCuaCay(TREE t, int &SumNodeTree)
{
	if(t != NULL)
	{
		SumNodeTree++;
		TongSoNodeCuaCay(t->pLeft,SumNodeTree);
		TongSoNodeCuaCay(t->pRight,SumNodeTree);
	}
}

int MAX(int a, int b)
{
	if(a > b)
	return a;
	else return b;
}

int DoCaoCuaCay(TREE t)
{
	if(t != NULL)
	{
		int t1 = DoCaoCuaCay(t->pLeft);
		int t2 = DoCaoCuaCay(t->pRight);
		return MAX(t1,t2)+1;
	}
	else
	return 0;
}









///////////////////////////////////XOA NODE//////////////////////////////////////
//Neu Node Can Xoa Co 2 Con
// Cach 1: Tim Node Trai Nhat Cua Cay Con Phai
// Cach 2: Tim Node Phai Nhat Cua Cay Con Trai




void DiTimNodeTheMang(TREE &Temp, TREE &X)//X = Temp->pRight
{
	//Duyet sang ben trai nhat cua cay con phai
	if(X->pLeft != NULL)
	{
		DiTimNodeTheMang(Temp,X->pLeft);//Duyet tiep de tim ra Node trai Nhat
	}
	else//luc nay X->pLeft == NULL --> Da Tim Duoc Node Trai Nhat
	{
		Temp->data = X->data;
		Temp = X;//Dua Node Xoa Gan bang Node The Mang
		X = X->pLeft;//tro toi NUll, vi no da la Node Trai Nhat
	}
}




void DeleleNode(TREE &t, int x)
{
	if( t == NULL )
	{
		cout<<"Khong Co Node De Xoa"<<endl;
		return;//ket thuc ham
	}
	else
	{
		if( x < t->data)
		{
			DeleleNode(t->pLeft,x);
		}
		else if(x > t->data)
		{
			DeleleNode(t->pRight,x);
		}
		
		else// x == t->data - Da tim ra Node Can Xoa
		{
			NODE *Temp = t;//Node Temp la Node the mang - la Node de chung ta xoa
			if(t->pLeft == NULL)//Node Chi Co 1 Cay Con Ben Phai
			{
				t = Temp->pRight;
			}
			else if(t->pRight == NULL)//Node Chi Co 1 Cay Con Ben Trai
			{
				t = Temp->pLeft;
			}
			
			else//Node Co 2 Cay Con Ben Phai Va Ben Trai
			{
				//cach 1: tim Node trai nhat cua cay con phai
				NODE *X = Temp->pRight;//Node X La Node The Mang Cho Node Can Xoa, Node nay se dam nhan nhiem vu tim ra Node trai nhat (cua cay con phai)
				DiTimNodeTheMang(Temp,X);
			}
			delete Temp;
		}
	}
}


void DeleteAllTree(TREE &t)
{
    if (t == NULL)
	{
        return;
    }
    if (t->pLeft != NULL)
	{
        DeleteAllTree(t->pLeft);
    }
    else if (t->pRight != NULL)
	{
    	DeleteAllTree(t->pRight);
    }
    delete t;
	// them vao cuoi
  	t = NULL;
}



////dem muc cua BST////
void CountLevelOfNode(TREE t, int &levelNode)//CORRECTLY
{
	if(t != NULL)
	{
		levelNode++;
		if(t->pLeft == NULL)
		{
			return;
		}
		else CountLevelOfNode(t->pLeft,levelNode);//duyet qua 1 ben cuoi cung
	}
}



bool LevelNodeLaCuaBST(TREE t, int x, int SumNodeLa,int &count, int levelNode)
{
	if(t != NULL)
	{
		x++;//duong di
		LevelNodeLaCuaBST(t->pLeft,x,SumNodeLa,count,levelNode);
		if(t->pLeft == NULL && t->pRight == NULL)//tai day la NodeLa
		{
			count++;//xac nhan da duyet duoc them 1 NodeLa
			if(x != levelNode)
			{
				return false;
			}
			else if(count == SumNodeLa)//da dem du so NodeLa return true
			{
				return true;
			}
			else
			 x-=1;
		}
		LevelNodeLaCuaBST(t->pRight,x,SumNodeLa,count,levelNode);
	}
}


void DoDaiDuongDiTuRootDenNode_X(TREE t, int x, int &path_length)
{
	if(t != NULL)
	{
		path_length++;
		if(x < t->data)
		{
			DoDaiDuongDiTuRootDenNode_X(t->pLeft,x,path_length);
		}
		else if(x > t->data)
		{
			DoDaiDuongDiTuRootDenNode_X(t->pRight,x,path_length);
		}
		else return;
	}
}



void ChieuCaoCayConTraiCuaNodeRoot(TREE t, int &length_SubLeftRoot)
{
	if(t != NULL)
	{
		length_SubLeftRoot++;
		ChieuCaoCayConTraiCuaNodeRoot(t->pLeft, length_SubLeftRoot);
	}
	else return;
}


void ChieuCaoCayConPhaiCuaNodeRoot(TREE t, int &length_SubRightRoot)
{
	if(t != NULL)
	{
		length_SubRightRoot++;
		ChieuCaoCayConPhaiCuaNodeRoot(t->pLeft, length_SubRightRoot);
	}
	else return;
}




void Menu(TREE &t)
{
	
	bool Init = false;
	int choice;
	while(true)
	{
		SetBGColor(3);
		SetColor(0);
		system("cls");
		cout<<"------------------------------MENU--------------------------"<<endl;
		cout<<"1. Khoi Tao Cay                                             "<<endl;
		cout<<"2. Kiem Tra BST Rong                                        "<<endl;
		cout<<"3. Them Node Vao BST                                        "<<endl;
		cout<<"4. Duyet BST                                                "<<endl;
		cout<<"5. Thong Tin Chi Tiet Cua BST                               "<<endl;
		cout<<"6. Tim Kiem Tren BST                                        "<<endl;
		cout<<"7. Xoa Node Trong BST                                       "<<endl;
		cout<<"8. Xoa Toan Bo BST                                          "<<endl;
		cout<<"9. Dem So Nguyen To Trong BST                               "<<endl;
		cout<<"10. Node Co Gia Tri Lon Nhat Trong BST                      "<<endl;
		cout<<"11. Xoa Nhieu Node trong BST                                "<<endl;
		cout<<"------------------------------------------------------------"<<endl;
		cout<<"Enter Choice: ";cin>>choice;
		
		switch(choice)
		{
			case 1:{
				InitTree(t);
				Init = true;
				cout<<"Init BST Success!"<<endl;system("pause");
				break;
			}
			
			case 2:{
				if(IsTreeEmpty(t) == true)
				{
					cout<<"BST Is Empty!!!"<<endl;system("pause");
				}
				else
				{
					cout<<"BST Is Not Empty!!!"<<endl;system("pause");
				}
				break;
			}
			
			case 3:{//them Node
				if(Init == false)
				{
					cout<<"BST Chua Duoc Khoi Tao"<<endl;system("pause");
					break;
				}
				
				int x;
				cout<<"Nhap Gia Tri Node De them Vao BST: ";cin>>x;
				bool result = AddNode(t,x);
				if(result == false)
				{
					cout<<"Add Node Fail (Error: Not Available or duplicate data"<<endl;system("pause");
				}
				break;
			}
			
			case 4:{
				if(Init == false || t == NULL)
				{
					cout<<"BST Is Empty!!!"<<endl;system("pause");
					break;
				}
				else
				{
					Duyet_LNR(t);
					cout<<endl<<"Traversal BST Success!"<<endl;system("pause");
					break;
				}

			}
			
			case 5:{
				SetColor(0);
				int select;
				cout<<"-------------MENU INFO OF BST--------------"<<endl;
				cout<<"1. So Node La Cua BST (Node Bac 0)         "<<endl;
				cout<<"2. So Node Co 1 Cay Con (Node Bac 1)       "<<endl;
				cout<<"3. So Node Co 2 Cay Con (Node Bac 2)       "<<endl;
				cout<<"4. So Node Chi Co 1 Cay Con Phai           "<<endl;
				cout<<"5. So Node Chi Co 1 Cay Con Trai           "<<endl;
				cout<<"6. Tong So Node Cua Cay                    "<<endl;
				cout<<"7. Do Cao Cua Cay                          "<<endl;
				cout<<"8. Cac Node Tren Tung Muc Cua Cay          "<<endl;
				cout<<"9. Do Dai Duong Di Tu Node Root Den Node X "<<endl;//gio cu lam theo: so canh de di toi Node can tim
				cout<<"10. Kiem Tra Co Phai La Cay Nhi Phan Dung  "<<endl;
				cout<<"11. Kiem Tra Co Phai la Cay Nhi Phan Day Du"<<endl;
				cout<<"12. Chieu Cao Cay Con Phai Va Trai Cua Node Root"<<endl;//chua lam
				
				cout<<"Enter Choice: ";cin>>select;
				switch(select)
				{
					case 1:{//So Node La Cua BST (Node Bac 0)
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int Nodela = 0;
							SoNodeLaCuaBST(t,Nodela);
							cout<<"So Node La Cua BST la: "<<Nodela<<endl;
							system("pause");
							break;
						}
					}
					
					case 2:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int Node1SubTree = 0;
							SoNodeCoMotCayCon(t,Node1SubTree);
							cout<<"So Node Co 1 Cay Con La: "<<Node1SubTree<<endl;
							system("pause");
							break;
						}
					}
					
					case 3:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int Node2SubTree = 0;
							SoNodeCoHaiCayCon(t,Node2SubTree);
							cout<<"So Node Co 2 Cay Con La: "<<Node2SubTree<<endl;
							system("pause");
							break;
						}
					}
					
					case 4:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int a = DemNodeChiCoMotCayConPhai(t);
							cout<<"So Node Chi Co Mot Cay Con Phai: "<<a<<endl;
							system("pause");
							break;
						}
					}
					
					case 5:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int b = DemNodeChiCoMotCayConTrai(t);
							cout<<"So Node Chi Co Mot Cay Con Trai: "<<b<<endl;
							system("pause");
							break;
						}
					}
					
					case 6:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int SumNode = 0;
							TongSoNodeCuaCay(t,SumNode);
							cout<<"Tong So Node Cua BST la: "<<SumNode<<endl;
							system("pause");break;
						}
					}
					
					case 7:{
						if(Init == false || t == NULL)
						{
							cout<<"BST Is Empty!!!"<<endl;system("pause");
							break;
						}
						else
						{
							int HightTree = DoCaoCuaCay(t);
							cout<<"Chieu Cao Cua BST la: "<<HightTree<<endl;
							system("pause");break;
						}
					}
					
					case 8:{
							Queue q;
							DuyetCaytheoMuc(t,q);
							system("pause");
						break;
					}
					
					case 9:{
						int x;
						cout<<"Nhap gia tri Node X: ";cin>>x;
						if(SearchNodeBST(t,x) == true)
						{
							int path_length = 0;
							DoDaiDuongDiTuRootDenNode_X(t,x,path_length);
							cout<<"Do Dai Tu Root Den X la: "<<path_length-1;
							system("pause");
						}
						else
						{
							cout<<"Node X khong ton tai trong BST"<<endl;system("pause");
						}
						
						break;
					}
					
					case 10:{//Kiem Tra BTree (Binary Tree) Co phai la cay nhi phan dung hay khong
					//CT: BTREE dung: Tong so nut = 2*NodeLa - 1
							int SumNodela = 0;
							int SumNode = 0;
							SoNodeLaCuaBST(t,SumNodela);
							TongSoNodeCuaCay(t,SumNode);
							if(SumNode == (2*SumNodela -1))
							{
								cout<<"DAY LA CAY NHI PHAN DUNG"<<endl;system("pause");
							}
							else
							{
								cout<<"KHONG PHAI LA CAY NHI PHAN DUNG"<<endl;system("pause");
							}
						break;
					}
					
					case 11:{//Kiem tra BTREE Co phai la cay nhi phan day hay khong
						//truoc het phai la cay nhi phan dung
						if(t == NULL)
						{
							if(Init == false || t == NULL)
							{
								cout<<"BST Is Empty!!!"<<endl;system("pause");
								break;
							}
						}
					
						else
						{
							int x = 0;
							int count = 0;
							int SumNodela = 0;
							int SumNode = 0;
							SoNodeLaCuaBST(t,SumNodela);
							TongSoNodeCuaCay(t,SumNode);
						
							int levelNode = 0;
							CountLevelOfNode(t,levelNode);//co duoc level Node

							if(SumNode == (2*SumNodela -1))//da la cay nhi phan dung thi moi xet tiep la cay nhi phan day du
							{
								if(LevelNodeLaCuaBST(t,x, SumNodela,count, levelNode) == false)
								{
									cout<<"KHONG PHAI LA CAY NHI PHAN DAY DU"<<endl;system("pause");
								}
								else
								{
									cout<<"LA CAY NHI PHAN DAY DU"<<endl;system("pause");
								}
							}
							else
							{
								cout<<"KHONG PHAI LA CAY NHI PHAN DAY DU"<<endl;system("pause");
							}
							break;
						}
					}
					
					case 12:{
						if(t == NULL)
						{
							if(Init == false || t == NULL)
							{
								cout<<"BST Is Empty!!!"<<endl;system("pause");
							}
						}
						
						else
						{
							int length_SubLeftRoot = 0;
							int length_SubRightRoot = 0;
							ChieuCaoCayConTraiCuaNodeRoot(t,length_SubLeftRoot);
							ChieuCaoCayConPhaiCuaNodeRoot(t,length_SubRightRoot);
							cout<<"Chieu Cao Cay Con Trai Cua Root: "<<length_SubLeftRoot-1<<endl;
							cout<<"Chieu Cao Cay Con Phai Cua Root: "<<length_SubRightRoot-1<<endl;
							system("pause");
						}
						
						break;
					}
					
					default: break;
				}
				break;
			}
			
			case 6:{
				
				if(Init == false || t == NULL)
				{
					cout<<"BST Is Empty!!!"<<endl;system("pause");
					break;
				}
				
				else
				{
					int FindItem;
					cout<<"Nhap Node Can Tim Kiem Trong BST: ";cin>>FindItem;
					if(searchNodeBST(t,FindItem) == true)
					{
						cout<<"CO TON TAI TRONG BST"<<endl;system("pause");
						break;
					}
					else
					{
						cout<<"KHONG TON TAI TRONG BST"<<endl;system("pause");
						break;
					}
				}
			}
			
			case 7:{
				
				if(Init == false || t == NULL)
				{
					cout<<"BST Is Empty!!!"<<endl;system("pause");
					break;
				}
				
				else
				{
					int DelNode;
					cout<<"Nhap Node Can Xoa: ";cin>>DelNode;
					if(SearchNodeBST(t,DelNode) != true)
					{
						cout<<"Node Can Xoa Khong Ton Tai"<<endl;system("pause");
						break;
					}
					else
					{
						DeleleNode(t,DelNode);
						cout<<"Delete Success!!!"<<endl;system("pause");
						break;
					}
				}
			}
			
			case 8:{
				
				if(Init == false || t == NULL)
				{
					cout<<"BST Is Empty!!!"<<endl;system("pause");
					break;
				}
				
				else
				{
					DeleteAllTree(t);
					cout<<"Delete All Node BST Success"<<endl;system("pause");
					break;
				}
				
			}
			
			case 9:{
				int demSNT = 0;
				DemSoLuongSoNguyenTo(t,demSNT);
				cout<<"So luong So Nguyen To: "<<demSNT<<endl;system("pause");
				break;
			}
			
			case 10:{
				int Max = -9999;
				TimMaxTrongBST(t,Max);
				cout<<"MAX Of BST is: "<<Max<<endl;system("pause");
				break;
			}
			
			case 11:{
				int soluongxoa;
				cout<< "So luong xoa: ";cin>>soluongxoa;
				int x;
				int array[soluongxoa];
				for(int i = 0 ; i < soluongxoa ; i++)
				{
					cout<<"Nhap x: ";
					cin>>x;
					array[i] = x;//mac dinh cac phan tu bang -1
				}
				
				for(int i = 0 ; i < soluongxoa; i++)
				{
					if(SearchNodeBST(t,array[i]) == true)
					{
						DeleleNode(t,array[i]);
					}
				}
				cout<<" Xoa cac Node thanh cong"<<endl;system("pause");
				break;
			}
			
			
			default: cout<<"Lua Chon Khong Hop Le"<<endl;system("pause");break;
		}                                                                                                                                                                                                                    
		
	}
}


int main()
{
	SetBGColor(3);
	SetColor(0);
	TREE t;
	Menu(t);
	system("pause");
	return 0;
}
