#include<vector>
#include<set>

#ifndef INFOSEC_DEGREETABLE_H
#define INFOSEC_DEGREETABLE_H

using namespace std;

class DegreeTable {
    friend ostream& operator<<(ostream& out, const DegreeTable& dg);
public:
    DegreeTable(int K, int L, int T);
    vector<int> alpha;
    vector<int> beta;
    const vector<int> &GetAlpha() const;
    const vector<int> &GetBeta() const;
    const int GetTermsSize() const;
private:
    void GASPbig();
    void GASPsmall();
    vector<vector<int>> a_outer_b;
    const int K, L, T;
    set<int> terms {};
};

ostream& operator<<(ostream& out, const DegreeTable& dg);

#endif //INFOSEC_DEGREETABLE_H
