#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

class cards {                       //class for all cards

    string color;
    int num;
    string type;
public:
    
    bool isFlipped = false;
    
    friend ostream & operator<< ( ostream &output, const cards &c ){
        output<< c.type<< c.num;
        return output;
    }

    void setColor(int c) {
        if(c==0)
            color = "black";
        else if(c==1)
            color = "red";
    }
    
    void setNum(int n) {
        num = n;
    }
    void setType(int t) {
        switch (t) {
            case 0: type = "spades"; break;
            case 1: type = "clubs"; break;
            case 2: type = "hearts"; break;
            case 3: type = "diamonds"; break;
        }
    }
    
    int getType() {
        if(type == "spades")
            return 1;
        else if(type == "clubs")
            return 2;
        else if(type == "heart")
            return 3;
        else if(type == "diamonds")
            return 4;
        else
            return 0;
    }
    
    int getNum() {
        return num;
    }
    
    int getColor() {
        if(type == "spades" || type == "clubs")
            return 1;
        else if(type == "hearts" || type == "diamonds")
            return 2;
        else
            return 0;
    }
    
    void display() {
        cout<<type<<num<<endl;
    }
    
    bool operator == (cards &rhs) {
        if((color == rhs.color)&&(num == rhs.num)&&(type == rhs.type))
            return true;
        else
            return false;
    }
};

vector<cards> MakePile(vector<cards> &pile, vector<cards> myDeck, vector<cards> tableauDeck, int opt) {     //first time initialization of the pile
    
    
    //assigning cards to the pile
    int c=0;
    int itr=0;
    do {
        
        int flag = 0;
        for(int i=0;i<28;i++) {
            if((myDeck.at(c) == tableauDeck.at(i))==true) {
                flag=1;
                break;
            }
        }
        
        if(flag==0) {
            pile.at(itr)=myDeck.at(c);
            itr+=1;
        }
        
        c+=1;
    } while (itr!=24);
    
    return pile;
}

void ShowPile(vector<cards> &pile, int pos) {       //shows the pile
    cout<<"Pile: ";
    
    for(int i=0;i<pile.size();i++) {
        if(i==(pos%24)) {
            cout<<pile.at(i);
            pile.at(i).isFlipped = true;
        }
        else {
            cout<<" * ";
            pile.at(i).isFlipped = false;
        }
    }
}

vector<cards> Tableau(vector<cards> myDeck, vector<cards> &row1, vector<cards> &row2, vector<cards> &row3, vector<cards> &row4, vector<cards> &row5, vector<cards> &row6, vector<cards> &row7) {            //first time initialization of the tableau
    vector<cards> tableauDeck(52);
    vector<int> random_nums(28);
    
    for(int r=0;r<28;r++) {
        random_nums.at(r) = rand()%52;
        for(int j=r;j>=0;j--) {
            if(random_nums.at(r)==random_nums.at(j))
                random_nums.at(r) = rand()%52;
        }
    }
    
    for(int i=0;i<28;i++) {
        tableauDeck.at(i) = myDeck.at(random_nums.at(i));
    }
    
    //first time setup for the tableau
    int i=0;
    for(i=0;i<1;i++)
        row1.at(i) = tableauDeck.at(i);
    row1.at(0).isFlipped = true;
    
    for(i=0;i<2;i++)
        row2.at(i) = tableauDeck.at(i+1);
    row2.at(1).isFlipped = true;
    
    for(i=0;i<3;i++)
        row3.at(i) = tableauDeck.at(i+3);
    row3.at(2).isFlipped = true;
    
    for(i=0;i<4;i++)
        row4.at(i) = tableauDeck.at(i+6);
    row4.at(3).isFlipped = true;
    
    for(i=0;i<5;i++)
        row5.at(i) = tableauDeck.at(i+10);
    row5.at(4).isFlipped = true;
    
    for(i=0;i<6;i++)
        row6.at(i) = tableauDeck.at(i+15);
    row6.at(5).isFlipped = true;
    
    for(i=0;i<7;i++)
        row7.at(i) = tableauDeck.at(i+21);
    row7.at(6).isFlipped = true;
    
    int j = 0;
    
    cout<<"1. ";
    for(j=0;j<1;j++) {
        if(row1.at(j).isFlipped == true)
            cout<<row1.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"2. ";
    for(j=0;j<2;j++) {
        if(row2.at(j).isFlipped == true)
            cout<<row2.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
    
     cout<<"3. ";
    for(j=0;j<3;j++) {
        if(row3.at(j).isFlipped == true)
            cout<<row3.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"4. ";
    for(j=0;j<4;j++) {
        if(row4.at(j).isFlipped == true)
            cout<<row4.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"5. ";
    for(j=0;j<5;j++) {
        if(row5.at(j).isFlipped == true)
            cout<<row5.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"6. ";
    for(j=0;j<6;j++) {
        if(row6.at(j).isFlipped == true)
            cout<<row6.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"7. ";
    for(j=0;j<7;j++) {
        if(row7.at(j).isFlipped == true)
            cout<<row7.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
    return tableauDeck;
}

void MoveCard(vector<cards> &row_init, int element, vector<cards> &row_fin) {           //move the cards inside the tableau
    int counter = 0;
    int size = row_fin.size()-1;
    if(element > row_init.size())
        cout<<"\n\nCARD SELECTION OUT OF RANGE. TRY AGAIN.\n\n";
    
    
    else if(row_init.at(element).isFlipped==true) {     //CHECK IF THE NUMBER BEING ADDED IS ONE LOWER THAN THE PREVIOUS ONE
        if((row_fin.at(size).getNum() - row_init.at(element).getNum()==1) && (row_fin.at(size).getColor()!=row_init.at(element).getColor())) {
            for(int i=element; i<row_init.size();i++) {
                row_fin.push_back(row_init.at(i));
                counter +=1;
            }
            //row_fin.resize(row_fin.size()+1); -- NOT REQUIRED
            row_init.resize(row_init.size()-counter);
            int i;
            for(i=0;i<row_init.size();i++);
            if(row_init.size()!=0)
                row_init.at(i-1).isFlipped = true;
        }
        else
            cout<<"\n\nCANNOT PLACE THE CARD THERE. TRY AGAIN.\n\n";
    }
    
    else if(row_init.at(element).isFlipped==false)
        cout<<"\n\nAll cards in the selected range are not flipped. TRY AGAIN.\n\n";
}

void showTableau(vector<cards> &row1, vector<cards> &row2, vector<cards> &row3, vector<cards> &row4, vector<cards> &row5, vector<cards> &row6, vector<cards> &row7) {               //show the tableau with all cards flipped/unflipped
    int j = 0;
    
    cout<<"1. ";
    for(j=0;j<row1.size();j++) {
        if(row1.at(j).isFlipped == true)
            cout<<" "<<row1.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
    cout<<"2. ";
    for(j=0;j<row2.size();j++) {
        if(row2.at(j).isFlipped == true)
            cout<<" "<<row2.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"3. ";
    for(j=0;j<row3.size();j++) {
        if(row3.at(j).isFlipped == true)
            cout<<" "<<row3.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"4. ";
    for(j=0;j<row4.size();j++) {
        if(row4.at(j).isFlipped == true)
            cout<<" "<<row4.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"5. ";
    for(j=0;j<row5.size();j++) {
        if(row5.at(j).isFlipped == true)
            cout<<" "<<row5.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
     cout<<"6. ";
    for(j=0;j<row6.size();j++) {
        if(row6.at(j).isFlipped == true)
            cout<<" "<<row6.at(j);
        else
            cout<<" * ";
    }
    cout<<endl;
    
    
     cout<<"7. ";
    for(j=0;j<row7.size();j++) {
        if(row7.at(j).isFlipped == true)
            cout<<" "<<row7.at(j);
        else
            cout<<" * ";
    }
    cout<<endl<<endl;
}

void Use_Pile(vector<cards> &pile, vector<cards> &target) {             //do actions with the pile
    int i, size;
    for(i=0;i<target.size();i++);
    size = i-1;
    
    for(int i=0;i<pile.size();i++) {
        if(pile.at(i).isFlipped==true) {
            if((target.at(size).getNum() - pile.at(i).getNum()==1) && (target.at(size).getColor()!=pile.at(i).getColor())) {
                    target.push_back(pile.at(i));
                    pile.erase(pile.begin()+i);
                }
            else
                cout<<"\n\nCANNOT PUT CARD TO THE TABLEAU\n\n";
        }
    }
}

bool Edit_Bin(vector<cards> &bin, vector<cards> &row) {             //add cards to the 4 bins
    
    int size_b, size,i;
    
    for(i=0;i<row.size();i++);
    size = i-1;
    for(i=0;i<bin.size();i++);
    size_b = i-1;
    
    if(bin.size()==0) {
        if(row.at(size).getNum()==1) {
            bin.push_back(row.at(size));
            row.erase(row.begin()+size);
            if(row.size()!=0)
                row.at(size-1).isFlipped=true;
        }
        else {
            cout<<"\n\nCANNOT PUT CARD TO THE BIN\n\n";
            return false;
        }
    }
    else if(bin.size()!=0) {
        if((bin.at(size_b).getNum() - row.at(size).getNum() == 1) && (bin.at(size_b).getType() == row.at(size).getType())) {
            bin.push_back(row.at(size));
            row.erase(row.begin()+size);
            if(row.size()!=0)
                row.at(size-1).isFlipped=true;
        }
        else {
            cout<<"\n\nCANNOT PUT CARD TO THE BIN\n\n";
            return false;
        }
    }
    else {
        cout<<"\n\nCANNOT PUT CARD TO THE BIN\n\n";
        return false;
    }
    return false;
}

void show_Bins(vector<cards> &bin1, vector<cards> &bin2, vector<cards> &bin3, vector<cards> &bin4) {        //displays the bins
    
    cout<<"\n\nBIN1: \n";
    for(int i=0;i<bin1.size();i++)
        cout<<bin1.at(i);
    
    cout<<"\nBIN2: \n";
    for(int i=0;i<bin2.size();i++)
        cout<<bin2.at(i);
    
    cout<<"\nBIN3: \n";
    for(int i=0;i<bin3.size();i++)
        cout<<bin3.at(i);
    
    cout<<"\nBIN4: \n";
    for(int i=0;i<bin4.size();i++)
        cout<<bin4.at(i);
    
    cout<<endl;
}

void pileToBin(vector<cards> &pile, vector<cards> &target) {
    int j, size;
    for(j=0;j<target.size();j++);
    size=j-1;
    
    if(target.size()==0) {
        for(int i=0;i<pile.size();i++) {
            if(pile.at(i).isFlipped==true) {
                if(pile.at(i).getNum()==1) {
                    target.push_back(pile.at(i));
                    pile.erase(pile.begin()+i);
                }
            }
        }
    }
    
    else if(target.size()!=0) {
        for(int i=0;i<pile.size();i++) {
            if(pile.at(i).isFlipped==true) {
                if((target.at(size).getNum() - pile.at(i).getNum()==1) && (target.at(size).getColor()!=pile.at(i).getColor())) {
                    target.push_back(pile.at(i));
                    pile.erase(pile.begin()+i);
                }
            }
        }
    }
    
    else
        cout<<"\n\nCANNOT PUT CARD TO THE BIN.\n\n";
}


void main_Game() {                  //game runs from here
    int opt, pos=-1, row_pile, bin, bin_pile, loop_ctr=0;
    int element, row_init, row_fin, row_bin;
    int history[1000];
RESTART:
    vector<cards> startingDeck(52);
    vector<cards> tableauDeck(52);
    
    vector<cards> pile(24);
    vector<cards> row1(1);
    vector<cards> row2(2);
    vector<cards> row3(3);
    vector<cards> row4(4);
    vector<cards> row5(5);
    vector<cards> row6(6);
    vector<cards> row7(7);
    
    vector<cards> bin1(0);
    vector<cards> bin2(0);
    vector<cards> bin3(0);
    vector<cards> bin4(0);
    
    //initialize card color in the deck
    for(int i=0; i<2; i++) {
        for(int j=(26*i); j<(26*2); j++){
            startingDeck[j].setColor(i);
        }
    }
    
    //initialize card number and type in the deck
    for(int i=0;i<13;i++) {
        startingDeck[i].setNum(i+1);
        startingDeck[i].setType(0);
    }
    
    for(int i=13;i<26;i++) {
        startingDeck[i].setNum(i-12);
        startingDeck[i].setType(1);
    }
    
    for(int i=26;i<39;i++) {
        startingDeck[i].setNum(i-25);
        startingDeck[i].setType(2);
    }
    
    for(int i=39;i<52;i++) {
        startingDeck[i].setNum(i-38);
        startingDeck[i].setType(3);
    }
    
    //place 28 cards randomly on the tableau
    tableauDeck = Tableau(startingDeck, row1, row2, row3, row4, row5, row6, row7);
    
    cout<<endl;
    
    //Show the pile
    MakePile(pile, startingDeck, tableauDeck, 0);
    ShowPile(pile, pos);
    show_Bins(bin1, bin2, bin3, bin4);
    cout<<endl;
    
    //`     showTableau(row1, row2, row3, row4, row5, row6, row7);
    bool flag=true, flag_win=false;
    int rep_ctr=0;
    do{
        for(int i=0;i<row1.size();i++) {
            if(row1.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row2.size();i++) {
            if(row2.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row3.size();i++) {
            if(row3.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row4.size();i++) {
            if(row4.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row5.size();i++) {
            if(row5.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row6.size();i++) {
            if(row6.at(i).isFlipped != true)
                flag_win=false;
        }
        for(int i=0;i<row7.size();i++) {
            if(row7.at(i).isFlipped != true)
                flag_win=false;
        }
        
        if(flag_win==true) {
            cout<<"\n\nYOU'VE WON THE GAME!\n\n";
            break;
        }
        cout<<"\n 1 : MOVE CARD\n 2 : REVEAL NEXT FROM PILE\n 3 : USE CARD FROM PILE ON TABLEAU\n 4 : PUT CARD FROM PILE TO BIN\n 5 : ADD CARD TO A BIN\n 6 : RESTART\n 7 : EXIT\n";
        cin>>opt;
        history[loop_ctr]=opt;
        
        /*
        for(int a=0;a<row;a++) {
            if(row1.at(a).isFlipped == true && row2.at(a).isFlipped == true && row3.at(a).isFlipped == true && row4.at(a).isFlipped == true && row5.at(a).isFlipped == true && row6.at(a).isFlipped == true && row7.at(a).isFlipped == true) {
                cout<<"YOU HAVE WON THE GAME!";
            }
        }
        */
        rep_ctr = 0;
        if(loop_ctr>30) {
            for(int c=1;c<31;c++) {
                if((history[loop_ctr-c]==2) && (history[loop_ctr]==2))
                    rep_ctr+=1;
            }
        }
        
        if(rep_ctr >= 30)
            flag = false;
        
        if(flag==false) {
            cout<<"\n\nNO MORE MOVES CAN BE MADE, YOU HAVE LOST THE GAME!\n\n";
        }
        
        if(opt==6) {
            pos = -1;
            cout<<"\nRESTARED\n\n";
            goto RESTART;
        }
        
        else if(opt==2) {
            pos+=1;
            
            showTableau(row1, row2, row3, row4, row5, row6, row7);
            ShowPile(pile, pos);
            show_Bins(bin1, bin2, bin3, bin4);
        }
        
        else if(opt==4) {
            cout<<"Choose bin: ";
            cin>>bin_pile;
            
            if(bin_pile==1)
                pileToBin(pile, bin1);
            if(bin_pile==2)
                pileToBin(pile, bin2);
            if(bin_pile==3)
                pileToBin(pile, bin3);
            if(bin_pile==4)
                pileToBin(pile, bin4);
            
            showTableau(row1, row2, row3, row4, row5, row6, row7);
            ShowPile(pile, pos);
            show_Bins(bin1, bin2, bin3, bin4);
        }
        
        else if(opt==5) {
            cout<<"Choose BIN: ";
            cin>>bin;
            
            cout<<"Choose row where the card lies: ";
            cin>>row_bin;
            
            if(bin==1 && row_bin==1)
                Edit_Bin(bin1, row1);
            else if(bin==1 && row_bin==2)
                Edit_Bin(bin1, row2);
            else if(bin==1 && row_bin==3)
                Edit_Bin(bin1, row3);
            else if(bin==1 && row_bin==4)
                Edit_Bin(bin1, row4);
            else if(bin==1 && row_bin==5)
                Edit_Bin(bin1, row5);
            else if(bin==1 && row_bin==6)
                Edit_Bin(bin1, row6);
            else if(bin==1 && row_bin==7)
                Edit_Bin(bin1, row7);
            
            else if(bin==2 && row_bin==1)
                Edit_Bin(bin2, row1);
            else if(bin==2 && row_bin==2)
                Edit_Bin(bin2, row2);
            else if(bin==2 && row_bin==3)
                Edit_Bin(bin2, row3);
            else if(bin==2 && row_bin==4)
                Edit_Bin(bin2, row4);
            else if(bin==2 && row_bin==5)
                Edit_Bin(bin2, row5);
            else if(bin==2 && row_bin==6)
                Edit_Bin(bin2, row6);
            else if(bin==2 && row_bin==7)
                Edit_Bin(bin2, row7);
            
            else if(bin==3 && row_bin==1)
                Edit_Bin(bin3, row1);
            else if(bin==3 && row_bin==2)
                Edit_Bin(bin3, row2);
            else if(bin==3 && row_bin==3)
                Edit_Bin(bin3, row3);
            else if(bin==3 && row_bin==4)
                Edit_Bin(bin3, row4);
            else if(bin==3 && row_bin==5)
                Edit_Bin(bin3, row5);
            else if(bin==3 && row_bin==6)
                Edit_Bin(bin3, row6);
            else if(bin==3 && row_bin==7)
                Edit_Bin(bin3, row7);
            
            else if(bin==4 && row_bin==1)
                Edit_Bin(bin4, row1);
            else if(bin==4 && row_bin==2)
                Edit_Bin(bin4, row2);
            else if(bin==4 && row_bin==3)
                Edit_Bin(bin4, row3);
            else if(bin==4 && row_bin==4)
                Edit_Bin(bin4, row4);
            else if(bin==4 && row_bin==5)
                Edit_Bin(bin4, row5);
            else if(bin==4 && row_bin==6)
                Edit_Bin(bin4, row6);
            else if(bin==4 && row_bin==7)
                Edit_Bin(bin4, row7);
            
            showTableau(row1, row2, row3, row4, row5, row6, row7);
            ShowPile(pile, pos);
            show_Bins(bin1, bin2, bin3, bin4);

        }
        
        else if(opt==3) {
            cout<<"Enter the row where you want to place the card: ";
            cin>>row_pile;
            
            if(row_pile == 1)
                Use_Pile(pile, row1);
            else if(row_pile == 2)
                Use_Pile(pile, row2);
            else if(row_pile == 3)
                Use_Pile(pile, row3);
            else if(row_pile == 4)
                Use_Pile(pile, row4);
            else if(row_pile == 5)
                Use_Pile(pile, row5);
            else if(row_pile == 6)
                Use_Pile(pile, row6);
            else if(row_pile == 7)
                Use_Pile(pile, row7);
            
            showTableau(row1, row2, row3, row4, row5, row6, row7);
            ShowPile(pile, pos);
            show_Bins(bin1, bin2, bin3, bin4);
        }
        
        else if(opt==1) {
            //moving a card on the tableau
            cout<<"\nRow number and card position of the card PICKED: ";
            cin>>row_init>>element;
            
            cout<<"\nRow where the picked card will be PLACED: ";
            cin>>row_fin;
            
            
            //CAN MAKE INTO A NEW FUNCTION -- CALLING TO CHANGE LOCATION OF CARDS
            if(row_init==1 && row_fin==2)
                MoveCard(row1, element-1, row2);
            else if(row_init==1 && row_fin==3)
                MoveCard(row1, element-1, row3);
            else if(row_init==1 && row_fin==4)
                MoveCard(row1, element-1, row4);
            else if(row_init==1 && row_fin==5)
                MoveCard(row1, element-1, row5);
            else if(row_init==1 && row_fin==6)
                MoveCard(row1, element-1, row6);
            else if(row_init==1 && row_fin==7)
                MoveCard(row1, element-1, row7);
            
            else if(row_init==2 && row_fin==1)
                MoveCard(row2, element-1, row1);
            else if(row_init==2 && row_fin==3)
                MoveCard(row2, element-1, row3);
            else if(row_init==2 && row_fin==4)
                MoveCard(row2, element-1, row4);
            else if(row_init==2 && row_fin==5)
                MoveCard(row2, element-1, row5);
            else if(row_init==2 && row_fin==6)
                MoveCard(row2, element-1, row6);
            else if(row_init==2 && row_fin==7)
                MoveCard(row2, element-1, row7);
            
            else if(row_init==3 && row_fin==1)
                MoveCard(row3, element-1, row1);
            else if(row_init==3 && row_fin==2)
                MoveCard(row3, element-1, row2);
            else if(row_init==3 && row_fin==4)
                MoveCard(row3, element-1, row4);
            else if(row_init==3 && row_fin==5)
                MoveCard(row3, element-1, row5);
            else if(row_init==3 && row_fin==6)
                MoveCard(row3, element-1, row6);
            else if(row_init==3 && row_fin==7)
                MoveCard(row3, element-1, row7);
            
            else if(row_init==4 && row_fin==1)
                MoveCard(row4, element-1, row1);
            else if(row_init==4 && row_fin==3)
                MoveCard(row4, element-1, row3);
            else if(row_init==4 && row_fin==2)
                MoveCard(row4, element-1, row2);
            else if(row_init==4 && row_fin==5)
                MoveCard(row4, element-1, row5);
            else if(row_init==4 && row_fin==6)
                MoveCard(row4, element-1, row6);
            else if(row_init==4 && row_fin==7)
                MoveCard(row4, element-1, row7);
            
            else if(row_init==5 && row_fin==1)
                MoveCard(row5, element-1, row1);
            else if(row_init==5 && row_fin==3)
                MoveCard(row5, element-1, row3);
            else if(row_init==5 && row_fin==4)
                MoveCard(row5, element-1, row4);
            else if(row_init==5 && row_fin==2)
                MoveCard(row5, element-1, row2);
            else if(row_init==5 && row_fin==6)
                MoveCard(row5, element-1, row6);
            else if(row_init==5 && row_fin==7)
                MoveCard(row5, element-1, row7);
            
            else if(row_init==6 && row_fin==1)
                MoveCard(row6, element-1, row1);
            else if(row_init==6 && row_fin==3)
                MoveCard(row6, element-1, row3);
            else if(row_init==6 && row_fin==4)
                MoveCard(row6, element-1, row4);
            else if(row_init==6 && row_fin==5)
                MoveCard(row6, element-1, row5);
            else if(row_init==6 && row_fin==2)
                MoveCard(row6, element-1, row2);
            else if(row_init==6 && row_fin==7)
                MoveCard(row6, element-1, row7);
            
            else if(row_init==7 && row_fin==1)
                MoveCard(row7, element-1, row1);
            else if(row_init==7 && row_fin==3)
                MoveCard(row7, element-1, row3);
            else if(row_init==7 && row_fin==4)
                MoveCard(row7, element-1, row4);
            else if(row_init==7 && row_fin==5)
                MoveCard(row7, element-1, row5);
            else if(row_init==7 && row_fin==6)
                MoveCard(row7, element-1, row6);
            else if(row_init==7 && row_fin==2)
                MoveCard(row7, element-1, row2);
            
            showTableau(row1, row2, row3, row4, row5, row6, row7);
            ShowPile(pile, pos);
            show_Bins(bin1, bin2, bin3, bin4);
            cout<<endl;
        }
        else if(opt==7)
            exit(0);
        
        loop_ctr += 1;
        cout<<"\n MOVES MADE: "<<loop_ctr<<"\n";
    }while(flag==true && flag_win==false);
}

class GameMenu {

public:
    GameMenu() {
        cout<<"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{SOLITAIRE}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"<<endl<<endl;
        cout<<"--------------------------------------------------Welcome!-----------------------------------------------------------"<<endl<<endl;
        startGame = 0;
    }

    GameMenu(int start){
        cout<<"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{SOLITAIRE}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"<<endl<<endl;
        cout<<"--------------------------------------------------Welcome!-----------------------------------------------------------"<<endl<<endl;
        startGame = start;
    }

    void setOption(int start){
        if(start == 1 || start == 2 || start == 3){
            startGame = start;
        }
    }
    void display(){
        cout<<"1. Start Game"<<endl;
        cout<<"2. Info"<<endl;
        cout<<"3. Quit"<<endl<<endl;
    }
    void menuItems(){
        if (startGame != 0){
            cin>>startGame;
        }
        display();
        int itr = 0;
        do {
            if (itr > 0){
                cout<<"Please selct a valid option (1, 2, 3)!"<<endl<<endl;
            }
            cin>>startGame;
            ++itr;
        } while((!(startGame == 1 || startGame == 2 || startGame == 3)));
        switch (startGame) {
        case 1:
                main_Game();
            break;
        case 2:
                cout<<"Made by Piyush Ranjan Sahu and Manvith Krishna Kandukuri."<<endl<<endl;
                break;
        case 3:
                exit(0);
                break;
        }
    }
    
private:
    int startGame;
};

int main() {    
    srand(time(NULL));
    GameMenu menu1;
    menu1.menuItems();
    //int num;
    //cout<<"Flip the pile? ";
    //cin >> num;

    return 0;
}
