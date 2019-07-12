#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <map>

#include <string.h>


#define OR ||
#define AND &&


using namespace std;


 map<string,string> symbols;


 double evalExpr(string expr)
{
    string xxx; // Get Rid of Spaces
    for (int i = 0; i < expr.length(); i++)
    {
        if (expr[i] != ' ')
        {
            xxx += expr[i];
        }
    }

    string tok = ""; // Do parantheses first
    for (int i = 0; i < xxx.length(); i++)
    {
        if (xxx[i] == '(')
        {
            int iter = 1;
            string token;
            i++;
            while (true)
            {
                if (xxx[i] == '(')
                {
                    iter++;
                } else if (xxx[i] == ')')
                {
                    iter--;
                    if (iter == 0)
                    {
                        i++;
                        break;
                    }
                }
                token += xxx[i];
                i++;
            }
            //cout << "(" << token << ")" << " == " << to_string(eval(token)) <<  endl;
            tok += to_string(evalExpr(token));
        }
        tok += xxx[i];
    }

    for (int i = 0; i < tok.length(); i++)
    {
        if (tok[i] == '+')
        {
            //cout << tok.substr(0, i) + " + " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) + eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return evalExpr(tok.substr(0, i)) + evalExpr(tok.substr(i+1, tok.length()-i-1));
        } else if (tok[i] == '-')
        {
            //cout << tok.substr(0, i) + " - " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) - eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return evalExpr(tok.substr(0, i)) - evalExpr(tok.substr(i+1, tok.length()-i-1));
        }
    }

    for (int i = 0; i < tok.length(); i++)
    {
        if (tok[i] == '*')
        {
            //cout << tok.substr(0, i) + " * " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) * eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return evalExpr(tok.substr(0, i)) * evalExpr(tok.substr(i+1, tok.length()-i-1));
        } else if (tok[i] == '/')
        {
            //cout << tok.substr(0, i) + " / " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) / eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return evalExpr(tok.substr(0, i)) / evalExpr(tok.substr(i+1, tok.length()-i-1));
        }
    }

    //cout << stod(tok.c_str()) << endl;
    return stod(tok.c_str()); // Return the value...
}


void print_tokens(vector <string> tokens)
{
    int i=0;

    for(i=0;i< tokens.size();i++)
    {
      cout << tokens[i]<<"\n";


    }
}

void print_map()
{

  map<string,string>::iterator itr;


   for (itr = symbols.begin(); itr != symbols.end(); itr++)
   {
        cout << itr->first
             << itr->second << '\n';
    }
 //cout<<symbols.size();

}



  void doAssign(string varname,string varvalue)
   {

          //cout <<symbols.size()<<"\n";
          symbols.insert({varname,varvalue});






   }


string getValue(string key)
{
        map<string,string>::iterator itr;




        for (itr = symbols.begin(); itr != symbols.end(); itr++)
   {
        if(itr->first==key)
            return itr->second;
    }


  return "Undefined variable "+key;


}


vector<string>::iterator getIterator(vector<string> temp,string element)
 {
   vector<string>::iterator it;

   for(it=temp.begin(); it != temp.end() ; it++)
   {
      if(*it == element)
           return it;

   }
     return it ;

 }

int getIndex(vector<string>temp,string element)
{
      int i;

      for(i=0;i<temp.size();i++)
      {
         if(temp[i]==element)
           return i;

      }


     return -1;

}

vector<string> trim(string from,string to,vector<string> tokens)
 {
       vector<string> temptok;

       int start_index,end_index;

       temptok = tokens;



       start_index = getIndex(temptok,from);

       temptok.erase(temptok.begin(), temptok.begin()+start_index+1);

       end_index = getIndex(temptok,to);
       temptok.erase(temptok.begin()+end_index, temptok.end());

       return temptok;

 }


 bool isNumber(string str)
 {
    int num;

    try
    {
        num = stoi(str);

    }

    catch(const exception& e)
    {
       return false;
    }


   return true;


}

 bool evalCondition_5(string type1,string operand1,string sign,string type2,string operand2)
 {

      int operand1_int,operand2_int;



     if(type1 == "VAR:")
     {
          operand1 = getValue(operand1);

          if(isNumber(operand1))
          {
             operand1_int = stoi(operand1);
             type1 = "NUM:";
          }

          else
             type1 = "STRING:";
    }

    if(type2 == "VAR:")
    {
         operand2 = getValue(operand2);

          if(isNumber(operand2))
          {
             operand2_int = stoi(operand2);
             type2 = "NUM:";

          }

          else
              type2 = "STRING:";

    }


	if(type1 == "NUM:")
            operand1_int = stoi(operand1);

    if(type2 == "NUM:")
            operand2_int = stoi(operand2);

    if(type1 == "EXPR:")
    {
           operand1 = to_string(evalExpr(operand1));
           operand1_int = stoi(operand1);
           type1 = "NUM:";
 	}

    if(type2 == "EXPR:")
    {
           operand2 = to_string(evalExpr(operand2));
           operand2_int = stoi(operand2);
           type2 = "NUM:";

     }

    if(type1 == "NUM:" && type2 =="NUM:")
    {

               if(sign == "GREATERTHAN:")
            {
                    if(operand1_int > operand2_int)
                         return true;

            }

               else if(sign == "LESSERTHAN:")
            {
                    if(operand1_int < operand2_int)
                         return true;

            }


     }


     else if( (type1 == "NUM:" AND type2 == "STRING:") OR (type1 == "STRING:" AND type2 == "NUM:") )
     {
         cerr<<"ERROR: Incompatible operands in conditional operation so else will be run automatically\n";


     }


  return false;

 }

 bool evalCondition_6(string type1,string operand1,string sign1,string sign2,string type2,string operand2)
  {

   int operand1_int,operand2_int;



     if(type1 == "VAR:")
     {
          operand1 = getValue(operand1);

          if(isNumber(operand1))
          {
             operand1_int = stoi(operand1);
             type1 = "NUM:";
          }

          else
             type1 = "STRING:";


      }

         if(type2 == "VAR:")
        {
          operand2 = getValue(operand2);

          if(isNumber(operand2))
          {
             operand2_int = stoi(operand2);
             type2 = "NUM:";

          }

          else
              type2 = "STRING:";

       }

     if(type1 == "NUM:")
            operand1_int = stoi(operand1);

     if(type2 == "NUM:")
            operand2_int = stoi(operand2);


     if(type1 == "EXPR:")
     {
           operand1 = to_string(evalExpr(operand1));
           operand1_int = stoi(operand1);
           type1 = "NUM:";

     }

      if(type2 == "EXPR:")
     {
           operand2 = to_string(evalExpr(operand2));
           operand2_int = stoi(operand2);
           type2 = "NUM:";

     }




     if(type1 == "NUM:" && type2 =="NUM:")
     {

            if(sign1 + sign2 == "EQUALS:EQUALS:")
            {
                if(operand1_int == operand2_int)
                     return true;

            }

           else if(sign1 + sign2 == "NOT:EQUALS:")
            {
                if(operand1_int != operand2_int)
                     return true;

            }



           else if(sign1 + sign2 == "GREATERTHAN:EQUALS:")
            {
                if(operand1_int >= operand2_int)
                     return true;

            }


           else if(sign1 + sign2 == "LESSERTHAN:EQUALS:")
            {
                if(operand1_int <= operand2_int)
                     return true;

            }

    }

     else if(type1 == "STRING:" && type2 == "STRING:")
    {


           if(sign1 + sign2 == "EQUALS:EQUALS:")
            {
                if(operand1 == operand2)
                     return true;

            }

            else if(sign1 + sign2 == "NOT:EQUALS:")
            {
                if(operand1 != operand2)
                     return true;

            }

     }



     else if( (type1 == "NUM:" AND type2 == "STRING:") OR (type1 == "STRING:" AND type2 == "NUM:") )
     {
         cerr<<"ERROR: Incompatible operands in conditional operation so else will be run automatically\n";


     }


  return false;

}

string convertVarExpr(string varexpr)
{
      string expr="";
      int i = 0;
      string tok="";
      char c;


      while(i<varexpr.length())
      {

          c = varexpr[i];


          if(c == '+' || c=='-' || c == '*' || c == '/' || c == '(' || c == ')'|| c == ';')
          {
            if(tok != "")
            {
               if(tok[0] == '$')
                      expr += getValue(tok);

               else
                   expr += tok;
            }

            if(c != ';')
               expr += c;

            tok = "";

          }


         else
         {
           tok+=c;
         }

         i++;

      }


  return expr;

}

int getNumberOfTokens(string start,string stop,vector<string> tokens)
{
    int start_index,end_index;

    start_index = getIndex(tokens,start);
    end_index = getIndex(tokens,stop);

    return end_index-start_index-1;

}

void parse(vector<string> tokens)
{
    int i=0,n;
    string input;
    vector<string> iftokens,elsetokens;
    bool condition;


    while(i < tokens.size())
    {

        if(tokens[i]+tokens[i+1]+tokens[i+3]== "PRINTSTRING:SEMICOLON:")
        {
               cout<<tokens[i+2]<<"\n";
               i+=4;
        }

        else if(tokens[i]+tokens[i+1]+tokens[i+3] == "PRINTNUM:SEMICOLON:")
        {
               cout<<tokens[i+2]<<"\n";
               i+=4;
        }

        else if(tokens[i]+tokens[i+1]+tokens[i+3] == "PRINTEXPR:SEMICOLON:")
        {
              cout << evalExpr(tokens[i+2])<<"\n";
              i+=4;

        }

        else if(tokens[i]+tokens[i+1]+tokens[i+3] == "PRINTVAREXPR:SEMICOLON:")
        {
              //cout << convertVarExpr(tokens[i+2]+";");
              cout << evalExpr(convertVarExpr(tokens[i+2]+";"))<<"\n";
              i+=4;

        }


           else if(tokens[i]+tokens[i+1]+tokens[i+3] == "PRINTVAR:SEMICOLON:")
        {
                cout <<getValue(tokens[i+2])<<"\n";
                i+=4;
        }




        else if(tokens[i]+tokens[i+2]+tokens[i+3]+tokens[i+5]== "VAR:EQUALS:STRING:SEMICOLON:")
         {

                doAssign(tokens[i+1],tokens[i+4]);
                i+=6;

         }

         else if(tokens[i]+tokens[i+2]+tokens[i+3]+tokens[i+5]== "VAR:EQUALS:NUM:SEMICOLON:")
         {

                doAssign(tokens[i+1],tokens[i+4]);
                i+=6;
         }

         else if(tokens[i]+tokens[i+2]+tokens[i+3]+tokens[i+5]== "VAR:EQUALS:EXPR:SEMICOLON:")
         {


                doAssign(tokens[i+1],to_string(evalExpr(tokens[i+4])));
                i+=6;
         }

         else if( tokens[i]+tokens[i+2]+tokens[i+3]+tokens[i+5]  == "VAR:EQUALS:VAREXPR:SEMICOLON:")
         {

               doAssign(tokens[i+1],to_string(evalExpr(convertVarExpr(tokens[i+4]+";"))));
               i+=6;

        }





        else if(tokens[i]+tokens[i+1]+tokens[i+3] == "INPUTVAR:SEMICOLON:")
        {
       			  getline(cin,input);
				  doAssign(tokens[i+2],input);
                  i+=4;
        }

         else if(tokens[i] == "IF")
         {

              iftokens = trim("IF-BEGIN:","IF-END:",tokens);
              elsetokens = trim("ELSE-BEGIN:","ELSE-END:",tokens);

              n = getNumberOfTokens("L-PARAN:","R-PARAN:",tokens);


              if(n==5)
                 condition = evalCondition_5(tokens[i+2],tokens[i+3],tokens[i+4],tokens[i+5],tokens[i+6]);

              else
                 condition = evalCondition_6(tokens[i+2],tokens[i+3],tokens[i+4],tokens[i+5],tokens[i+6],tokens[i+7]);

               if(condition)
              {
                 parse(iftokens);
                 i = i+5+n+iftokens.size();
                 i = i+3+elsetokens.size();
              }

              else
              {
				 i = i+5+n+iftokens.size();
				 parse(elsetokens);
                 i = i+3+elsetokens.size();
              }

		 }


	 }

  }



int main(int argc,char *args[])
{


  ifstream file;

  string filename = args[1];

  string variable;

  vector<string> tokens;


  char c;
  string tok="",str="",var="",expr="";
  int state = 0,ifstarted=0,elsestarted=0,exprstarted=0,varexprstarted=0;

  file.open(filename);




 while( (c=file.get()) != EOF )
  {

     tok += c;

    if(tok == " " || tok == "\n")
    {

      if(state == 0)
         tok = "";

    }

    if(tok == "\" ")
         tok = "";



   else if(tok == "PRINT" OR tok == "print")
   {
     tokens.push_back("PRINT");
	 tok ="";
   }

   else if(tok == "INPUT" OR tok == "input")
   {
	   tokens.push_back("INPUT");
	   tok = "";
   }

   else if(tok == "\"")
   {
     if(state==0)
     {
      state =1;
      tok ="";
     }

     else
     {
       tokens.push_back("STRING:");
       tokens.push_back(str);
       tok = "";
       str="";
       state=0;
     }

    }

    else if(state == 1)
    {
      str += tok;
      tok = "";
    }



    else if(state == 0 AND (tok=="0" || tok=="1" || tok =="2" || tok == "3" || tok == "4" || tok == "5" || tok =="6" || tok == "7" || tok == "8" || tok =="9"))
    {
       if(var != "")
       {
            var += tok;
            tok = "";
       }
       else
       {
            expr+= tok;
            tok = "";
       }

    }


    else if(state == 0 AND (tok == "+" || tok == "-" || tok == "*" || tok == "/") )
    {


          if(var != "")
          {
              varexprstarted = 1;
              var += tok;
              tok = "";

          }

           else if(expr != "")
           {

                exprstarted=1;
                expr+= tok;
                tok="";

           }

    }

    else if(tok == "$" && state == 0)
    {

           var += tok;
           tok = "";
    }




    else if(tok == ")" )
    {

          if(ifstarted==0)
          {

             expr += tok;
             tok ="";
          }


           else if(expr!= "")
           {

                    if(exprstarted==1)
                    {
                        tokens.push_back("EXPR:");
                        tokens.push_back(expr);

                    }

                    else
                    {
                        tokens.push_back("NUM:");
                        tokens.push_back(expr);

                    }

               tokens.push_back("R-PARAN:");
               expr = "";
               tok = "";

              }

              else if(var != "")
              {

                  if(varexprstarted == 0)
                  {
                        tokens.push_back("VAR:");
                        tokens.push_back(var);

                  }



                  else
                 {

                        tokens.push_back("VAREXPR:");
                        tokens.push_back(var);
                 }

               tokens.push_back("R-PARAN:");
               tok = "";
               var = "";

            }



        }




    else if(tok == ";" )
    {

     if(expr!= "")
      {
         if(exprstarted==1)
         {
               tokens.push_back("EXPR:");
               tokens.push_back(expr);
               exprstarted=0;
               expr = "";
         }

         else
         {
               tokens.push_back("NUM:");
               tokens.push_back(expr);
               expr = "";

         }

      }

      else if(var != "")
      {
           if(varexprstarted == 1)
           {
              tokens.push_back("VAREXPR:");
              tokens.push_back(var);
              varexprstarted=0;
              var = "";

           }

           else
           {
              tokens.push_back("VAR:");
              tokens.push_back(var);
              var = "";

           }
      }



      tokens.push_back("SEMICOLON:");
      tok = "";
    }


    else if(tok == "=")
    {

          if(var != "")
          {
               if(varexprstarted == 0)
               {
                    tokens.push_back("VAR:");
                    tokens.push_back(var);
                    tokens.push_back("EQUALS:");
                    var = "";
                    tok = "";
               }

               else
               {
                    tokens.push_back("VAREXPR:");
                    tokens.push_back(var);
                    tokens.push_back("EQUALS:");
                    var = "";
                    tok = "";
                    varexprstarted = 0;
               }

          }


         else if(expr != "")
         {

                if(exprstarted==1)
               {
                    tokens.push_back("EXPR:");
                    tokens.push_back(expr);
                    tokens.push_back("EQUALS:");
                    expr = "";
                    tok = "";
                    exprstarted =0;
               }

                else
               {
                    tokens.push_back("NUM:");
                    tokens.push_back(expr);
                    tokens.push_back("EQUALS:");
                    expr = "";
                    tok = "";

               }

         }

         else
         {
              tokens.push_back("EQUALS:");
              tok = "";

         }


    }




       else if(tok == ">")
    {
          if(var != "")
            {
               if(varexprstarted == 0)
               {
                    tokens.push_back("VAR:");
                    tokens.push_back(var);
                    tokens.push_back("GREATERTHAN:");
                    var = "";
                    tok = "";
               }

               else
               {
                    tokens.push_back("VAREXPR:");
                    tokens.push_back(var);
                    tokens.push_back("GREATERTHAN:");
                    var = "";
                    tok = "";
                    varexprstarted = 0;
               }

          }


         else if(expr != "")
         {

                if(exprstarted==1)
               {
                    tokens.push_back("EXPR:");
                    tokens.push_back(expr);
                    tokens.push_back("GREATERTHAN:");
                    expr = "";
                    tok = "";
                    exprstarted =0;
               }

                else
               {
                    tokens.push_back("NUM:");
                    tokens.push_back(expr);
                    tokens.push_back("GREATERTHAN:");
                    expr = "";
                    tok = "";
                    exprstarted =0;

               }

         }

         else
         {
              tokens.push_back("GREATERTHAN:");
              tok = "";

         }


    }




       else if(tok == "<")
    {
            if(var != "")
             {
                 if(varexprstarted == 0)
                {
                    tokens.push_back("VAR:");
                    tokens.push_back(var);
                    tokens.push_back("LESSERTHAN:");
                    var = "";
                    tok = "";
                }

                else
                {
                    tokens.push_back("VAREXPR:");
                    tokens.push_back(var);
                    tokens.push_back("LESSERTHAN:");
                    var = "";
                    tok = "";
                    varexprstarted = 0;
               }

          }



         else if(expr != "")
         {

                if(exprstarted==1)
               {
                    tokens.push_back("EXPR:");
                    tokens.push_back(expr);
                    tokens.push_back("LESSERTHAN:");
                    expr = "";
                    tok = "";
                    exprstarted =0;
               }

                else
               {
                    tokens.push_back("NUM:");
                    tokens.push_back(expr);
                    tokens.push_back("LESSERTHAN:");
                    expr = "";
                    tok = "";
                    exprstarted =0;

               }

         }

         else
         {
              tokens.push_back("LESSERTHAN:");
              tok = "";

         }


    }


       else if(tok == "!")
     {
          if(var != "")
            {
               if(varexprstarted == 0)
               {
                    tokens.push_back("VAR:");
                    tokens.push_back(var);
                    tokens.push_back("NOT:");
                    var = "";
                    tok = "";
               }

               else
               {
                    tokens.push_back("VAREXPR:");
                    tokens.push_back(var);
                    tokens.push_back("NOT:");
                    var = "";
                    tok = "";
                    varexprstarted = 0;
               }

          }



         else if(expr != "")
         {

                if(exprstarted==1)
               {
                    tokens.push_back("EXPR:");
                    tokens.push_back(expr);
                    tokens.push_back("NOT:");
                    expr = "";
                    tok = "";
                    exprstarted =0;
               }

                else
               {
                    tokens.push_back("NUM:");
                    tokens.push_back(expr);
                    tokens.push_back("NOT:");
                    expr = "";
                    tok = "";
                    exprstarted =0;

               }

         }

         else
         {
              tokens.push_back("NOT:");
              tok = "";

         }


    }






    else if(var != "")
    {
           var+= tok;
		   tok = "";
    }



    else if(tok == "if" OR tok =="IF")
    {
           ifstarted=1;
           tokens.push_back("IF");
           tok = "";
    }

    else if(tok == "else" OR tok == "ELSE")
    {
           elsestarted=1;
           tokens.push_back("ELSE");
           tok = "";
    }

    else if(tok == "(")
    {

         if(ifstarted==0)
      {
         expr += tok;
         tok ="";
      }

      else
      {
          tokens.push_back("L-PARAN:");
          tok = "";

      }
    }




    else if(tok == "{")
    {
          if(ifstarted==1 AND elsestarted==1)
          {
               tokens.push_back("ELSEIF-BEGIN:");
               tok = "";

          }
          else if(ifstarted == 1)
          {

                 tokens.push_back("IF-BEGIN:");
                 tok = "";
          }

          else if(elsestarted==1)
          {
                tokens.push_back("ELSE-BEGIN:");
                tok = "";
          }

    }

    else if(tok == "}")
    {
         if(ifstarted==1 AND elsestarted==1)
         {
            tokens.push_back("ELSEIF-END:");
            tok = "";
            ifstarted=0;
            elsestarted=0;

         }



         else if(ifstarted==1)
        {

            tokens.push_back("IF-END:");
            tok = "";
            ifstarted=0;
        }

        else if(elsestarted==1)
        {
            tokens.push_back("ELSE-END:");
            tok = "";
            elsestarted=0;
        }

    }



    }

file.close();


parse(tokens);
//print_tokens(tokens);

return 0;

}



