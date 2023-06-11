#include <bits/stdc++.h>
using namespace std;
const char separator    = ' ';
const int numWidth      = 10;
double h;
double ob1sum=0,ob2sum=0;
int ii;
bool bb=false;
unordered_map<int,int> mp;
void print_table(vector<double> objective, vector<double> objective2, vector<vector<double>> constraint,int u,vector<string> basic, vector<double> eq,int m)
{
    cout.precision(2);
    string s;
    s+='X';
    cout << left << setw(numWidth) << setfill(separator) << " ";
    for(int i=0; i < u+1; ++i) {
        if(bb && mp[i]) continue;
        string uu= s;
        uu+= to_string(i+1);
        cout << left << setw(numWidth) << setfill(separator) << fixed << uu;
    }
    cout << '|' << "    " << "Sol\n\n";
    cout << left << setw(numWidth) << setfill(separator) << "Z";
    for(int i=0; i < u+1; ++i) {if(bb && mp[i]) continue;cout << left << setw(numWidth) << setfill(separator) << fixed << objective[i];}
    cout << '|' << "    " << ob1sum;
    cout << endl << endl;
    if(!bb) {
        cout << left << setw(numWidth) << setfill(separator) << "Z'";
        for (int i = 0; i < u + 1; ++i) cout << left << setw(numWidth) << setfill(separator) << fixed << objective2[i];
        cout << '|' << "    " << ob2sum;
        cout << endl << endl;
    }
    for(int i=0; i < m; ++i)
    {
        cout << left << setw(numWidth) << setfill(separator) << basic[i];
        cout << left << setw(numWidth) << setfill(separator);
        for(int j=0; j < u+1; ++j){if(bb && mp[j]) continue; cout << left << setw(numWidth) << setfill(separator) << fixed <<constraint[i][j];}
        cout << '|' << "    " << eq[i];
        cout << endl << endl;
    }
    cout << endl;
    for(int i=0; i < u+4; ++i)
    {
        cout << left << setw(numWidth) << setfill(separator) << "___";
    }
    cout << endl << endl << endl;
}
void modify_table_row(int colum,vector<double> &v1,vector<double> &v2)
{
    h = -v2[colum] / v1[colum];
    for (int i = 0; i < 100; ++i) {
        v2[i] += v1[i] * h;
    }
}
int SN(vector<double> &v)
{
    double j=1;
    int b=-1;
    for(int i=0; i < v.size(); ++i)
    {
        if(mp[i] && bb) continue;
        if(v[i] < 0)
        {
            if(v[i] < j)
            {
                j=v[i];
                b=i;
            }

        }
    }
    return b;
}
int basic_number(string s)
{
    string g;
    for(int i=1; i < s.length(); ++i) g+=s[i];
    return stoi(g)-1;
}
int SP(vector<double> &v)
{
    double j=999999;
    int b=-1;
    for(int i=0; i < v.size(); ++i)
    {
        if(v[i] > 0)
        {
            if(v[i] < j)
            {
                j=v[i];
                b=i;
            }

        }
    }
    return b;
}
int check(vector<double> objective,vector<string> &basic,int u)
{
    for(int i=0; i < u+1; ++i)
    {
        if(bb && mp[i]) continue;
        bool aaa=false,bbb=true;
        if(objective[i] < 1e-6) aaa=true;
        for(auto & j : basic)
        {
            int g = basic_number(j);
            if(g == i) bbb=false;
        }
        if(aaa&&bbb) return i+1;
    }
    return 0;
}

void solve ()
{
    cout << "Enter the number of variables\n";
    int n; cin >> n;
    vector<double> objective(1000,0),objective2(1000,0);
    int u = n-1;
    cout << "Enter the coefficients of the objective function Example: 3X1 - 7X2 is writen as '3 -7' without the quotation marks \n";
    for(int i=0; i < n; ++i) {cin >> objective[i]; objective[i]*=-1;}
    cout << "Enter the number of the constraints\n";
    int m;  cin >> m;
    vector<vector<double>> constraint(1000,vector<double>(1000,0));
    vector<double> eq(m); vector<string> basic(m,"X");
    for(int i=0; i < m; ++i)
    {
        if(i != 0){cout << "Enter the coefficients of constraint number "; cout << i+1 << endl;}
        if(i == 0){cout << "Enter the coefficients of constraint number "; cout << i+1 << endl; cout << "Example: 5X1-17X2 <= 8 is written as '5 -17 < 8' \n";}
        for(int j=0; j < n; ++j) {
            cin >> constraint[i][j];
        }
        char w; cin >>w;
        cin >> eq[i];
        if(w== '<') {u++; constraint[i][u]=1; basic[i]+=to_string(u+1);}
        else if(w == '>'){u++; constraint[i][u]=-1;objective2[u+1]=1; mp[u+1]=1; constraint[i][u+1]=1;u++; basic[i]+=to_string(u+1);}
        else {u++; constraint[i][u]=1; mp[u]=1;basic[i]+=to_string(u+1);objective2[u]=1;}
    }
    cout << "Initial tableau\n\n";
    print_table(objective,objective2,constraint,u,basic,eq,m);
    double f=0;
    for( ii=0; ii < basic.size(); ++ii)
    {
        modify_table_row(basic_number(basic[ii]),constraint[ii],objective2);
        ob2sum+=h*eq[ii];
        f+= h;
        modify_table_row(basic_number(basic[ii]),constraint[ii],objective);
        ob1sum+=h*eq[ii];
    }
    if(f != 0)print_table(objective,objective2,constraint,u,basic,eq,m);
    while(ob2sum!=0 && SN(objective2)!=-1)
    {
        int c = SN(objective2);
        vector<double> k=eq;
        for(int i=0; i < k.size(); ++i) {
            if(constraint[i][c] < 1e-6 ) {k[i]=-1; continue;}
            k[i] /= constraint[i][c];
        }
        int r = SP(k);
        if(r==-1) {
            cout << "The solution is unbounded\n";
            return;
        }
        basic[r]="x"+ to_string(c+1);
        modify_table_row(basic_number(basic[r]),constraint[r],objective2);
        ob2sum+=h*eq[r];
        modify_table_row(basic_number(basic[r]),constraint[r],objective);
        ob1sum+=h*eq[r];
        for(int i=0; i < basic.size(); ++i)
        {
            if(i == r) continue;
            modify_table_row(basic_number(basic[r]),constraint[r],constraint[i]);
            eq[i]+=h*eq[r];
        }
        h = constraint[r][c];
        for(int i=0; i < u+1; ++i) constraint[r][i]/=h;
        eq[r]/=h;
        print_table(objective,objective2,constraint,u,basic,eq,m);
    }
    double hh = ob2sum;
    if(ob2sum > 1e-6 && SN(objective2)==-1)
    {
        cout << "Infeasible solution because there is not a single negative coefficient in Z' and the value of Z' didn't reach zero\n";
        return;
    }

    bb=true;
    cout << "Phase 1 is finishes because Z' became equal to zero so we can now remove Z' and the artificial variables from the table\n\n";
    print_table(objective,objective2,constraint,u,basic,eq,m);
        while (SN(objective) != -1) {
            int c = SN(objective);
            vector<double> k = eq;
            for (int i = 0; i < k.size(); ++i) {
                if (constraint[i][c] < 1e-6) {
                    k[i] = -1;
                    continue;
                }
                k[i] /= constraint[i][c];
            }
            int r = SP(k);
            if (r == -1) {
                cout << "The solution is unbounded because at the ratio test we cannot find any positive value\n";
                return;
            }
            basic[r] = "x" + to_string(c + 1);
            modify_table_row(basic_number(basic[r]), constraint[r], objective);
            ob1sum += h * eq[r];
            for (int i = 0; i < basic.size(); ++i) {
                if (i == r) continue;
                modify_table_row(basic_number(basic[r]), constraint[r], constraint[i]);
                eq[i] += h * eq[r];
            }
            h = constraint[r][c];
            for (int i = 0; i < u + 1; ++i) constraint[r][i] /= h;
            eq[r] /= h;
            print_table(objective, objective2, constraint, u, basic, eq, m);
    }
        cout << "The Objective function is equal to " << ob1sum << endl;
        for (int i = 0; i < basic.size(); ++i) {
            cout << basic[i] << " = " << eq[i] << endl;
        }
        if (check(objective, basic,u)) {
            cout << "\n\nSince there is a non basic that is equal to zero the solution is alternative\n\n                      One other solution  \n\n";
            int c = check(objective, basic,u) - 1;
             vector<double>k = eq;
            for (int i = 0; i < k.size(); ++i) {
                if (constraint[i][c] < 1e-6) {
                    k[i] = -1;
                    continue;
                }
                k[i] /= constraint[i][c];
            }
            int r = SP(k);
            basic[r] = "x" + to_string(c + 1);
            for (int i = 0; i < basic.size(); ++i) {
                if (i == r) continue;
                modify_table_row(basic_number(basic[r]), constraint[r], constraint[i]);
                eq[i] += h * eq[r];
            }
            h = constraint[r][c];
            for (int i = 0; i < u + 1; ++i) constraint[r][i] /= h;
            eq[r] /= h;
            print_table(objective, objective2, constraint, u, basic, eq, m);

            for (int i = 0; i < basic.size(); ++i) {
                cout << basic[i] << " = " << eq[i] << endl;
            }
        }
}
int main()
{
    int t=1; //cin >> t;
    while(t--) {
        solve();
    }
}
