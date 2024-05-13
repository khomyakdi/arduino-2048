class GameField {
public:
  int **field;

  GameField() {
    field = new int*[4];
    for(int i = 0; i < 4; i++)
      field[i] = new int[4];

    resetField();
  }
 
  void shiftTop() {
    bool moved = false;
    bool switched = true;

    while (switched == true) {
      switched = false;
      for (int i = 0; i < 4; i++)
        for (int j = 3; j > 0; j--) {
          if (field[j - 1][i] == 0 && field[j][i]!=0) {
            switchElements(j - 1, i, j, i);
            switched = true;
            moved = true;
          }
        }
    }

    for (int j = 0; j < 4; j++)
      for (int i = 0; i < 3; i++)
        if (field[i][j] == field[i + 1][j] && field[i][j] != 0) {
          for (int k = i + 1; k < 3; k++)
            field[k][j] = field[k + 1][j];
          
          field[i][j] *= 2;
          field[3][j] = 0;
          moved = true;
        }
    
    prepateNextMove(moved);
  }

  void shiftBottom() {
    bool switched = true;
    bool moved = false;
    while (switched == true) {
      switched = false;
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
          if (field[j + 1][i] == 0 && field[j][ i] != 0) {
            switchElements(j + 1, i, j, i);
            switched = true;
            moved = true;
          }
    }
      
    for(int j=0;j< 4; j++)
      for(int i= 3;i>0;i--)
        if(field[i][j]== field[i-1][j]&& field[i][j]!=0) {
          for(int k=i;k>0;k--)
            field[k][j]= field[k-1][j];

          field[i][j]*=2;
          field[0][j]=0;
          moved = true;
        }
    
   prepateNextMove(moved);
  }

  void shiftLeft() {
    bool switched = true;
    bool moved = false;
    
    while (switched == true) {
      switched = false;
      for (int j = 0; j < 4; j++)
        for (int i = 3; i > 0; i--)
          if (field[j][i - 1] == 0 && field[j][i] != 0) {
            switchElements(j, i-1, j, i);
            switched = true;
            moved = true;
          }
    }
          
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 3; j++)
        if (field[i][j] == field[i][j + 1] && field[i][j] != 0) {
          for (int j2 = j + 1; j2 < 3; j2++)
            field[i][j2] = field[i][j2 + 1];
          
          field[i][j] *= 2;
          field[i][3] = 0;
          moved = true;
        }
    
    prepateNextMove(moved);
  }

  void shiftRight() {
    bool switched = true;
    bool moved = false;
    while (switched == true) {
      switched = false;
      for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
          if (field[j][i + 1] == 0 && field[j][i] != 0) {
            switchElements(j, i+1, j, i);
            switched = true;
            moved = true;
          }
    }
    
    for (int i = 0; i < 4; i++) 
      for (int j = 3; j > 0; j--)
        if (field[i][j] == field[i][ j - 1] && field[i][j] != 0) {
          for (int j2 = j - 1; j2 > 0; j2--)
            field[i][j2] = field[i][j2 - 1];
          
          field[i][ j] *= 2;
          field[i][0] = 0;
          moved = true;
        }
    
    prepateNextMove(moved);
  }

private:
  void prepateNextMove(bool shifted) {
    if(!shifted && !hasMoves()) {
      resetField();
      return;
    }

    if(!shifted)
      return;

    setRandomElement();
  }

  bool containsEmpty() {
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        if(field[i][j] == 0)
          return true;

    return false;
  }

  void switchElements(int x1, int y1, int x2, int y2) {
    field[x1][y1] += field[x2][y2];
    field[x2][y2] = field[x1][y1] - field[x2][y2];
    field[x1][x2] -= field[x2][y2];
  }

  void setRandomElement() {
    int value = random(0, 2) == 0 ? 2 : 4;

    if(containsEmpty())
      while(true) {
        int x = random(0, 4);
        int y = random(0, 4);
        
        if(field[x][y] == 0) {
          field[x][y] = value;
          break;
        }
      }
  } 

  void resetField() {
    for(int i = 0; i < 4; i++)
      for(int j = 0; j < 4; j++)
        field[i][j] = 0;  

    setRandomElement();
  }

  bool hasMoves() {
    for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
        if(field[i][j] == field[i][j + 1] || field[i][j] == field[i + 1][j])
          return true;
          
    for(int i = 0; i < 3; i++)
      if(field[i][3]==field[i+1][3])
        return true;

    for(int i = 0; i < 3; i++)
      if(field[3][i]==field[3][i + 1])
        return true;

    return false;            
  }
};