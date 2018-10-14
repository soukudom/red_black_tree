#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class NotFoundException {
  public:
    NotFoundException() {}
    friend ostream& operator<<(ostream& os, const NotFoundException& e ) {os << "Value not found" ;return os;}
};

  class CValue
  {
    //private:
    public:
        int value;
    //public:
      CValue();
      //CValue(const CValue &i); nejsem si uplne jistej
      //~CValue();
    //  CValue& operator = ( const CValue &i );
     // bool operator == ( const CValue &i ) const;
     // bool operator != ( const CValue &i ) const;
     // bool operator < ( const CValue &i ) const;
     // bool operator > ( const CValue &i ) const;
     // bool operator >= ( const CValue &i ) const;
     // bool operator <= ( const CValue &i ) const;

  };

  class CKey
  {
    //private:
    public:
        int key;
    public:
      CKey();
      //CKey(const CKey &i);
      //~CKey();
     // CKey& operator = ( const CKey &i );
      bool operator == ( const CKey &i ) const;
      bool operator != ( const CKey &i ) const;
      bool operator < ( const CKey &i ) const;
      //bool operator > ( const CKey &i ) const;
      bool operator >= ( const CKey &i ) const;
      //bool operator <= ( const CKey &i ) const;

  };
  #endif  /* __PROGTEST__*/

class CNode {
public:
    char color;
    CNode *parent;
    CNode *left;
    CNode *right;
    mutable CKey key;
    mutable CValue value;
//public:
  CNode(const CKey& key,const CValue& value);
  char getColor() const;
  CNode* getParent() const;
  CNode* getLeft() const;
  CNode* getRight() const;
  CKey& getKey() const;
  CValue& getValue() const;
};

class CTable {
//private:
public:
    CNode *root;
//public:
  CTable();
  ~CTable();
  bool insert(const CKey& key, const CValue& val);
  bool remove(const CKey& key);
  CValue search(const CKey& key) const;
  bool isElem(const CKey& key) const;
  CNode *getRoot() const;

  void dealokace(CNode * uk);

  bool findInsertNode(CNode * item);
  void checkCase1(CNode * item);
  void checkCase2(CNode * item);
  void checkCase3(CNode * item);
  void checkCase4(CNode * item);
  void checkCase5(CNode * item);
  CNode *getGrandParent(CNode * item);
  CNode *getUncle(CNode * item);
  CNode *rotateLeft(CNode * item);
  CNode *rotateRight(CNode * item);

  int deleteNode(const CKey &key, CNode **item);
  CNode *getPredecessor(CNode *item);
  CNode *getSibling(CNode *item);
  void deleteCase1(CNode * sibling);
  bool deleteCase2(CNode * sibling);
  void deleteCase3P(CNode * sibling);
  void deleteCase3L(CNode * sibling);
  void deleteCase4P(CNode * sibling);
  void deleteCase4L(CNode * sibling);
  int consolidate(CNode * item);
  CNode * rotateRightDel(CNode * item);
  CNode * rotateLeftDel(CNode * item);

};

//================================================================ implementace CValue ===============================================
#ifndef __PROGTEST__

CValue::CValue(){
    value=0;
}
//=============================== implementace CKey ===============================


CKey::CKey(){
    key = 0;
}

bool CKey::operator==(const CKey &i) const{
    if( key == i.key)
        return true;
    else
        return false;
}

bool CKey::operator<(const CKey &i) const{
    if( key < i.key)
        return true;
    else
        return false;
}

bool CKey::operator>=(const CKey &i) const{
    if( key >= i.key)
        return true;
    else
        return false;
}

bool CKey::operator != ( const CKey &i ) const{
    if (key != i.key){
        return true;
    }
    else{
        return false;
    }
}
#endif  /* __PROGTEST__*/

//======================== implementace CTable ================================

CTable::CTable(){
    root = NULL;
}

CTable::~CTable(){
//projdi postorder a smaz co zbylo
    dealokace(root);
   // delete root;
    root = NULL;
    //cout << root << endl;
}

void CTable::dealokace(CNode * uk){
    if(uk == NULL) return;
    dealokace(uk->left);
    dealokace(uk->right);
    delete uk;
    uk = NULL;

}

bool CTable::insert(const CKey& key, const CValue& val){
    CNode * item = new CNode(key,val);
    //pripad 1
    if(root == NULL){
     //   cout << "prvni prvek" << endl;
        root = item;
        //item->color = 'B';
        checkCase1(item);
        return true;

    }
   // CKey h = root->getKey();
   // cout << "jdu vkladat" << key.key << " v root" << h.key << root << " color" << root->color << endl;

    bool res =findInsertNode(item);
    if(res == false){
        delete item;
        return false;
    }

  //  cout << "vlozeno a jdu kontrolovat" << endl;
    checkCase1(item);
    //cout << item.getColor() << endl;
    return true;


}

bool CTable::remove(const CKey& key){
    CNode *item = NULL;
    //CNode *sibling = NULL;
    CNode *dele = NULL;
    //bool left = false;
    int result = deleteNode(key,&item);
    int res = 3;
   // cout << "budu mazat " << item->color << endl;
    if(item != NULL && item->color == 'X'){
        dele = item;
    }
    if(result == 2){
        //neni co mazat
        return false;
    }
    if(result == 0){
        //delete item;
        item = NULL;
        return true;
    }

    if(result == 1){
        //return true;
        do{
            if(res == 2){
                item = item->parent;
                if(item->parent == NULL){
        //            cout << root->left->color << endl;
                    if(dele !=NULL){
                        //mazani prvku
                        if(dele->parent->left == dele){
                            dele->parent->left = NULL;
                            delete dele;
                            dele = NULL;
                        }
                        else{
                            dele->parent->right = NULL;
                            delete dele;
                            dele = NULL;

                        }

                    }
                    return true;
                }
            }
 //           cout << "dalsi konsolidace "<< item->getKey().key << endl;
            res = consolidate(item);
        }while(res != 0);
      //  cout << "koncim konsolidaci" << endl;
    }
    if(dele !=NULL){
     //mazani prvku
            if(dele->parent->left == dele){
                    dele->parent->left = NULL;
                    delete dele;
                    dele = NULL;
            }
            else{
                dele->parent->right = NULL;
                delete dele;
                dele = NULL;

            }

    }
    return true;

}

int CTable::consolidate(CNode * item){
    //    cout << "jdu hledat sibling" << endl;
        CNode *sibling = getSibling(item);
 //       cout << "sibling je " << sibling->getKey().key << endl;

      //  cout << "jdu konsolidovat "<< endl;
        if(sibling->color == 'R'){
    //        cout << "case1" << endl;
            deleteCase1(sibling);
            //cout << "orotovano" << endl;
            return 1;
        }
        if(sibling->color == 'B' && ((sibling->left != NULL && sibling->right != NULL && sibling->left->color == 'B' && sibling->right->color == 'B') || (sibling->left == NULL && sibling->right == NULL ))){
    //        cout << "case2" << endl;
            bool res = deleteCase2(sibling);
       //     cout << "case2 color " << sibling->color << endl;
            if(res == true){
                return 0;
            }
            else{
                return 2; //nove se to bude volat na rodice

            }
        }
        if(sibling->parent->right == sibling && sibling->color == 'B'){
    //    cout << "case 3L nebo 4P" << endl;
        //    cout << sibling->left->color << sibling->right <<endl;
            if(sibling->right != NULL && sibling->right->color == 'R'){
    //            cout << "case 3L" << endl;
                deleteCase3L(sibling);
            }
            else if(sibling->left != NULL && sibling->left->color == 'R' && (sibling->right == NULL || sibling->right->color == 'B')){
   //             cout << "case 4P" << endl;
                deleteCase4P(sibling);
            }
            return 0;
        }
        if(sibling->parent->left == sibling && sibling->color == 'B'){
            if(sibling->left != NULL && sibling->left->color == 'R'){
                deleteCase3P(sibling);
            }
            else if(sibling->right !=NULL && sibling->right->color == 'R' && (sibling->left == NULL || sibling->left->color == 'B')){
                deleteCase4L(sibling);
            }
            return 0;
        }
    return 0;

}

CValue CTable::search(const CKey& key) const{
    CNode * pom = getRoot();
    while(pom != NULL && pom->getKey() != key)
    {
        if( pom->getKey() <  key)
            pom = pom->getRight();
        else{
            pom = pom->getLeft();
        }
    }
    if(pom != NULL){
        return pom->getValue();
    }
    else{
        throw NotFoundException();
    }
}

bool CTable::isElem(const CKey& key) const{
    try{
        search(key);
    }
    catch(...){
        return false;
    }
    return true;

}

void CTable::deleteCase1(CNode * sibling){
  //  cout << "upravuju podle deleteCase1" << endl;
    if(sibling->parent->right == sibling){//pravej syn
   //     cout << "levej syn" << endl;
        sibling->parent->color='R';
        sibling->color='B';
        rotateLeftDel(sibling->parent);

    }
    else{//levej syn
    //    cout << "levej syn" << endl;
    //    cout << sibling->getKey().key << endl;
        sibling->parent->color='R';
        sibling->color='B';
        rotateRightDel(sibling->parent);

    }

}
bool CTable::deleteCase2(CNode * sibling){
//cout << "upravuju podle deleteCase2!" << endl;
    sibling->color = 'R';
  //  cout << "prebarveno" << endl;
    if(sibling->parent->color == 'R'){
        sibling->parent->color = 'B';
        return true;
    }
    else{
     //   cout << "jdu na dalsi kolo konsolidace" << endl;
//        sibling->parent->color = 'X';
        return false;
    }
    //vracet true jestli se ma jeste pokracovat nebo ne !!!
}
void CTable::deleteCase3L(CNode * sibling){
//cout << "upravuju podle deleteCase3L" << endl;
    //swap S and P
    char color = sibling->color;
    sibling->color = sibling->parent->color;
    sibling->parent->color = color;
  //  cout << "provedl jsem swap barev" << endl;
   // cout << sibling->parent->getKey().key << endl;
    rotateLeftDel(sibling->parent);
 //   cout << neco->left->getKey().key << endl;
    sibling->right->color = 'B';

}

void CTable::deleteCase3P(CNode * sibling){
//cout << "upravuju podle deleteCase3P" << endl;
    //swap S and P
    char color = sibling->color;
    sibling->color = sibling->parent->color;
    sibling->parent->color = color;
    rotateRightDel(sibling->parent);
    //cout << "orotovano " << root->left->getKey().key  << endl;
    sibling->left->color = 'B';

}

void CTable::deleteCase4P(CNode * sibling){
//cout << "upravuju podle deleteCase4P" << endl;

    char color = sibling->color;
    sibling->color = sibling->left->color;
    sibling->left->color = color;
 //   cout << "pred 4 rotaci:" << root->left->getKey().key << endl;
    rotateRightDel(sibling);
  //  cout << "po 4P rotaci:" << root->right->getKey().key << endl;
    deleteCase3L(sibling->parent);
  //  cout << "po 3P rotaci:" << endl;

}

void CTable::deleteCase4L(CNode * sibling){
//cout << "upravuju podle deleteCase4L" << endl;
    char color = sibling->color;
    sibling->color = sibling->right->color;
    sibling->right->color = color;

    rotateLeftDel(sibling);
    deleteCase3L(sibling->parent);

}




CNode *CTable::getRoot() const{
    return root;
}

  CNode *CTable::getPredecessor(CNode *item){
    while(item->right != NULL){
    //    cout << "posun " << item->getKey().key << endl;
        item = item->right;
    }
    //cout << "getPredecesor " << item->left->getKey().key << endl;
    return item;

  }

  CNode *CTable::getSibling(CNode *item){
    if(item->parent == NULL){
    //    cout << "uzel nema rodice" << endl;
        return NULL;
    }
    CNode *parent = item->parent;
    if(item == parent->left){
    //    cout << "vracim " << parent->right->getKey().key  << endl;
        return parent->right;
    }
    else{
     //   cout << "vracim " << parent->left->getKey().key << endl;
        return parent->left;
    }
  }

int CTable::deleteNode(const CKey & key,CNode **item){
    //najdi uzel
     CNode * pom = getRoot();
     CNode * tmp_parent = NULL;
     bool left = false;
     //najdu uzel
    while(pom != NULL && pom->getKey() != key)
    {
        tmp_parent = pom;
        if( pom->getKey() < key){
            pom = pom->getRight();
            left = false;
        }
        else{
            pom = pom->getLeft();
            left = true;
        }
    }
 //   cout << "nasel jsem uzel"<< pom->getKey().key << endl;
    *item = pom;
   // cout << "jdu mazat "<< pom->getKey().key <<" " << pom->color<< left<< endl;
    if(pom != NULL){
        //ma oba synyv

        //cout << "testovani na oba potomky" << endl;
        if( pom->left != NULL && pom->right != NULL){
 //           cout << "ma oba potomky"  << endl;
           // cout << "BARVA "<<pom->left->left->getKey().key << endl;
            CNode * tmp = getPredecessor(pom->left);
            //cout << "dalsi " << pom->left->getKey().key << endl;
 //           cout << "predchuce " << tmp->getKey().key<< endl;
            pom->key = tmp->getKey();
            pom->value = tmp->getValue();

       //     if(pom->color == 'R'){
  //              cout << "dva potomci: " << endl;
                if(tmp->left == NULL && tmp->right == NULL){
   //                 cout << "dva potomci list" << endl;
                    if(tmp->color == 'B'){
                        tmp->color = 'X';
                        *item = tmp;
   //                     cout << "cernej list" << endl;
                        return 1;
                    }
                    else{
                        if(tmp->parent->left == tmp){
                            tmp->parent->left = NULL;
                            delete tmp;
                            *item = NULL;
                            return 0;
                        }
                        else{
                            tmp->parent->right = NULL;
                            delete tmp;
                            *item = NULL;
                            return 0;
                        }
                    }
                }
                else{
                    if(tmp->left->color == 'B'){
                        tmp->color = 'X';
                        *item=tmp;
                        return 1;
                    }
                    else{
                    CNode * help = pom->left;
                    pom->left = pom->left->left;
                    pom->left->color = 'B';
                    pom->left->parent = pom;
                    delete help;
                    }
                }
                return 0;
        }
        //ma jednoho syna
       // cout << "testovani na jednoho potomka" << endl;
        else if((pom->left == NULL && pom->right != NULL) || (pom->right == NULL && pom->left !=NULL)){

 //           cout << "ma jednoho potomka" << endl;

            //pokud ma mazany uzel leveho syna
            if(pom->left != NULL){
             //   cout << "ma levyha potomka" << endl;
                if(tmp_parent == NULL){
                        root = pom->left;
                        pom->left->parent = NULL;
                        pom->left->color = 'B';
                        delete pom;
                        *item=NULL;
                        //pom=NULL;
                        return 0;
                    }

                //pokud jsem prisel zleva
                if(left == true){

                    tmp_parent->left = pom->left;
                }
                else{
                    tmp_parent->right = pom->left;
                }
                //nastaveni ukazatele na rodice
                pom->left->parent = tmp_parent;
                //zmena barvy
       //         if(pom->left->color == 'R'){
                    pom->left->color = 'B';
                    delete pom;
                    *item=NULL;
                    return 0;

         //       }
         //       else{
         //           pom->left->color = 'X';
         //      }


            }
            else{
           //     cout << "ma pravyho potomka" << endl;
                if(tmp_parent == NULL){
                        root = pom->right;
                        pom->right->parent = NULL;
                        pom->right->color = 'B';
                        delete pom;
                        *item=NULL;
                        return 0;
                    }


                if(left == true){
                    tmp_parent->left = pom->right;
                }
                else{
                    tmp_parent->right = pom->right;
                }
                //nastaveni ukazatele na rodice
                pom->right->parent = tmp_parent;
                //zmena barvy
    //            if(pom->right->color == 'R'){
                    pom->right->color = 'B';
                    delete pom;
                    *item = NULL;
                    return 0;
      //          }

       //         else{
       //             pom->right->color = 'X';
        //            return 1;
       //         }

            }
        }
        //cout << "testovani na list " << endl;
        //je to list
        else{
 //           cout << "je to list " <<  pom->color <<endl;
            if(pom->color == 'R'){
                if(left == true){
//                    cout << "je levej" << endl;
                    tmp_parent->left = NULL;
                    delete pom;
                    *item=NULL;
                }
                else{
 //                   cout << "je pravej" << endl;
                    tmp_parent->right = NULL;
                    delete pom;
                    *item = NULL;
 //                   cout << "smazano" << endl;
                }
 //               cout << "return 0" << endl;
                return 0;
            }
            else{
                if(tmp_parent == NULL){
                    delete pom;
                    *item = NULL;
                    root = NULL;
                    return 0;
                }
 //               cout << "je cernej" << endl;
                pom->color = 'X';
                return 1;
            }

        }

       // parent = &tmp_parent;
        return 1;
    }
    else{
        //neni co mazat
        return 2;
    }
 }

bool CTable::findInsertNode(CNode *item){
    CNode * pom = getRoot();
    CNode * tmp_parent = NULL;


    while(pom != NULL && pom->getKey() != item->getKey())
    {
        tmp_parent = pom;
        if( pom->getKey() <  item->getKey()){
 //           cout << "posouvam doprava" << endl;
            pom = pom->getRight();
        }
        else{
 //           cout << "posouvam doleva" << endl;
            pom = pom->getLeft();
        }
    }
    if(pom == NULL){
        if(tmp_parent->getKey() < item->getKey()){
 //           cout << "vkladam vetsi" << endl;
            tmp_parent->right = item;
            item->parent = tmp_parent;
        }
        else{
 //           cout << "vkladam mensi" << endl;
            tmp_parent->left = item;
            item->parent = tmp_parent;
        }
        return true;
    }
    else{
 //       cout << "prepisuju value" << endl;
        pom->value = item->value;
        return false;
    }
}

CNode *CTable::getGrandParent(CNode * item){
    if(item != NULL && item->parent != NULL){
        return item->parent->parent;
    }
    else{
        return NULL;
    }
}

CNode *CTable::getUncle(CNode * item){
    CNode *gp = getGrandParent(item);
    if(gp == NULL){
        return NULL;
    }
    if(item->getParent() == gp->getLeft()){
        return gp->getRight();
    }
    else{
        return gp->getLeft();
    }

}

CNode * CTable::rotateLeft(CNode * item){
    CNode * tmp = item->right;
    item->right = tmp->left;
    if(item->right != NULL){
        item->right->parent = item;
    }
    tmp->parent = item->parent;
    tmp->left = item;
    //moje uprava !!!!!
    if(item->parent != NULL)
        item->parent->left=tmp;

    item->parent = tmp;

    if(tmp->parent == NULL){
 //       cout << "provedena korekce rootu" << endl;
        root = tmp;
    }
    return tmp;

}

CNode * CTable::rotateLeftDel(CNode * item){
    CNode * tmp = item->right;
    //cout << item->parent->getKey().key << endl;
    item->right = tmp->left;
    if(item->right != NULL){
        item->right->parent = item;
    }
    tmp->parent = item->parent;
    tmp->left = item;
    //moje uprava !!!!!
    if(item->parent != NULL){
    //    cout << "nastavuju rodice v rotaci rotaceLeftDel" << endl;
        if(item->parent->right == item){
    //        cout << "pravej rodic" << endl;
            item->parent->right=tmp;
        }
        else{
           // cout << tmp->parent->getKey().key << endl;
    //        cout << "levej rodic" << endl;
            item->parent->left=tmp;
        }
    }

    item->parent = tmp;
    if(tmp->parent == NULL){
 //       cout << "provedena korekce rootu v rotaci" << endl;
        root = tmp;
    }
    return tmp;

}

CNode * CTable::rotateRight(CNode * item){
  //  cout << "rotace "<< item->getKey().key << endl;
    CNode * tmp = item->left;
    item->left = tmp->right;
    if(item->left != NULL){
        item->left->parent = item;
    }
    tmp->parent = item->parent;
    tmp->right = item;
    //moje uprava !!!!!
    if(item->parent != NULL)
        item->parent->right=tmp;

    item->parent = tmp;

    if(tmp->parent == NULL){
        root = tmp;
    }
 //   cout << "rotace "<< tmp->right->getKey().key << " root " << root->right->getKey().key<< endl;
    return tmp;

}

CNode * CTable::rotateRightDel(CNode * item){
  //  cout << "rotace "<< item->getKey().key << endl;
    CNode * tmp = item->left;
    item->left = tmp->right;
    if(item->left != NULL){
        item->left->parent = item;
    }
    tmp->parent = item->parent;
    tmp->right = item;
    //moje uprava !!!!!
    if(item->parent != NULL){
//        cout << "nastavuji rodice v rotaci rotaceRightDel" << endl;
        if(item->parent->right == item){
//            cout << "pravej" << endl;
            item->parent->right=tmp;
        }
        else{
//            cout << "levej" << endl;
            item->parent->left=tmp;
        }
    }
    item->parent = tmp;

    if(tmp->parent == NULL){
        root = tmp;
    }
 //   cout << "rotace "<< tmp->right->getKey().key << " root " << root->right->getKey().key<< endl;
    return tmp;

}


void CTable::checkCase1(CNode * item){
 //   cout << "pripad 1" << endl;
    if(item->getParent() == NULL){
        item->color = 'B';
    }
    else{
 //       cout << "jdu na pripad 2" << endl;
        checkCase2(item);
    }

}

void CTable::checkCase2(CNode * item){
//cout << "pripad 2" << endl;
    CNode *tmp_parent = item->getParent();
    if(tmp_parent->color != 'B'){
  //      cout << "jdu na pripad 3"<< endl;
        checkCase3(item);
    }

}


void CTable::checkCase3(CNode * item){
//cout << "pripad 3" << endl;
    CNode *uncle = getUncle(item);

    if(uncle != NULL && uncle->getColor() == 'R'){
  //      cout << "uncle " << uncle->getKey().key << endl;
        item->parent->color = 'B';
        uncle->color = 'B';
        CNode *gp = getGrandParent(item);
        gp->color = 'R';
 //       cout << "jdu zpet na pripad 1" << endl;
        checkCase1(gp);
    }
    else{
 //   cout << "jdu na pripad 4"<< endl;
        checkCase4(item);
    }

}

void CTable::checkCase4(CNode * item){
//cout << "pripad 4" << endl;
    CNode *gp = getGrandParent(item);
    if(item == item->parent->right && item->parent == gp->left){
       // cout << "4: leva rotace" << endl;
        rotateLeft(item->parent);
        item = item->left;
    }
    else{
        if(item == item->parent->left && item->parent == gp->right){
       // cout <<"4: prava rotace "<< endl;
        rotateRight(item->parent);
       // cout << item->getKey().key << endl;
        item = item->right;
      /*  cout << item->getKey().key << endl;
        cout << item->parent->getKey().key << endl;
        cout << item->parent->parent->getKey().key << endl;*/

        }

    }
   // cout << "jdu na pripad 5"<< endl;
    checkCase5(item);

}

void CTable::checkCase5(CNode * item){
    CNode * gp = getGrandParent(item);
    item->parent->color = 'B';
    gp->color = 'R';
    if(item == item->parent->left && item->parent == gp->left){
       // cout <<"rotace doprava" << endl;
        rotateRight(gp);
    }
    else{
        if(item == item->parent->right && item->parent == gp->right ){
    //        cout << "rotace doleva" << endl;
            rotateLeft(gp);
        }
    }

}

//================== implemetace CNode ==========================

CNode::CNode(const CKey& key,const CValue& value){
    color = 'R';
    parent = NULL;
    left = NULL;
    right = NULL;
    this->key = key;
    this->value = value;
}

char CNode::getColor() const{
    return color;
}

CNode* CNode::getParent() const{
    return parent;
}

CNode* CNode::getLeft() const{
    return left;
}
CNode* CNode::getRight() const{
    return right;
}

CKey& CNode::getKey() const{

    return key;
}

CValue& CNode::getValue() const{
    return value;
}




//================================ main =========================================
#ifndef __PROGTEST__
int main(int argc, char ** argv){

    CTable x;
    CKey a,b,c,d,e,f,g,h,ch,i,j,k,l,m,n,o;
    CValue z,y;
    z.value=5;

    a.key=10;
    b.key=85;

    c.key=15;
    d.key=70;

    e.key=20;
    f.key=60;

    g.key=30;
    h.key=50;

    ch.key=65;
    i.key=80;

    j.key=90;
    k.key=40;

     l.key=5;
      m.key=55;
//-----------------
    n.key = 7;
    o.key=111;

    //x.insert(CKey(),CValue());
    x.insert(a,CValue());
    x.insert(b,CValue());
    x.insert(c,CValue());
    x.insert(d,CValue());
    x.insert(e,CValue());
    x.insert(f,CValue());
    x.insert(g,CValue());
    x.insert(h,CValue());
    x.insert(ch,CValue());
    x.insert(i,CValue());
    x.insert(j,CValue());
     x.insert(k,CValue());
     x.insert(l,CValue());
      x.insert(m,CValue());

   // x.insert(n,z);

    //bool y = x.isElem(c);

    cout << "*********************** dalsi" << endl;
    x.remove(j);
    bool result = x.isElem(j);
    cout << result << endl;
      cout << "*********************** dalsi" << endl;
    x.remove(b);
    result = x.isElem(j);
    cout << result << endl;

  cout << "*********************** dalsi" << endl;
    x.remove(g);
    result = x.isElem(j);
    cout << result << endl;
      cout << "*********************** dalsi" << endl;
    x.remove(e);
    result = x.isElem(j);
    cout << result << endl;
    cout << x.root->left->left->left->getKey().key << endl;

      cout << "*********************** dalsi" << endl;
    x.remove(d);
    result = x.isElem(j);
    cout << result << endl;
    cout << x.root->left->getKey().key << endl;

    cout << "*********************** dalsi" << endl;
    x.remove(c);

    result = x.isElem(c);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;
    x.remove(ch);
    cout << x.root->right->getKey().key << endl;
    cout << x.root->right->getValue().value << endl;
    cout << x.root->right->color << endl;
    result = x.isElem(ch);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;
    x.remove(i);
    result = x.isElem(i);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;
     x.remove(l);
    result = x.isElem(l);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;

    x.remove(a);
    result = x.isElem(a);
    cout << result << endl;
    cout <<  x.root->left->parent->getKey().key << endl;
    cout << "*********************** dalsi" << endl;

     x.remove(k);
     result = x.isElem(k);
    cout << result << endl;
    cout << x.root->getKey().key << endl;
    cout << x.root->getValue().value << endl;
    cout << x.root->color << endl;
    cout << "*********************** dalsi" << endl;
    x.remove(f);
     result = x.isElem(f);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;
    x.remove(m);
     result = x.isElem(m);
    cout << result << endl;
    cout << "*********************** dalsi" << endl;
    x.remove(h);
     result = x.isElem(h);
    cout << result << endl;
    cout << x.root << endl;
    cout << "*********************** dalsi" << endl;




     x.insert(a,CValue());
    x.insert(a,z);
    x.insert(c,CValue());
    x.remove(a);
    x.remove(a);
    x.remove(a);

   // x.insert(n,z);

    //bool y = x.isElem(c);

/*    CValue y(3);
    if(x == y){
        cout << "ano" << endl;
    }
    else{
        cout << "ne" << endl;
    }*/
}

