#include<bits/stdc++.h>
using namespace std;
int N; uint64_t b[64], s; uint64_t a[64];
pair<uint64_t, uint64_t> L[8388608]; 
pair<uint64_t, uint64_t> R[8388608];
pair<uint64_t, uint64_t> tmp[8388608];
void merge(pair<uint64_t, uint64_t> A[], uint64_t val, int size)
{
    for(int i=0; i<size; ++i)
        A[i].second *= 2;
    for(int i=0; i<size; ++i)
    {
        A[size+i] = A[i];
        A[size+i].first += val;
        A[size+i].second ++;
    }
}
string solve_inv()
{
    uint64_t b0 = b[0];
    while(b0%2==0) b0/=2;
    uint64_t b0inv = 1;
    uint64_t b0pow = b0; 
    for(int i=0; i<90; ++i)
    {
        b0inv *= b0pow;
        b0pow *= b0pow;
    }
    for(uint64_t i=1;;i += 2)
    {
        uint64_t rinv = b0inv * i;
        bool flag = true;
        uint64_t psum = 0;
        for(int j=0; j<N; ++j)
        {
            a[j] = b[j] * rinv;
            if(i==283)
            {
                cout <<"RINV";
                cout << rinv << endl;
                cout << a[j] << endl;
            }
            if(a[j] <= psum)
            {
                flag = false; break;
            }
            uint64_t x = psum + a[j];
            if(x < psum)
            {
                flag = false; break;
            }
            psum += a[j];
        }
        if(!flag) continue;
        uint64_t srinv = s*rinv;
        string res = "";
        for(int i=N-1; i>=0; --i)
        {
            if(srinv>=a[i])
            {
                res = "1" + res;
                srinv -= a[i];
            }
            else res = "0" + res;
        }
        //cout << i << endl;
        return res;
    }
}
string solve_naive()
{
    int lv = N/2;
    int rv = (N+1)/2;
    for(int i=0; i<lv; ++i)
        merge(L, b[i], 1<<i);
    for(int i=0; i<rv; ++i)
        merge(R, b[lv+i], 1<<i);
    sort(L, L+(1<<lv));
    sort(R, R+(1<<rv));
    for(int i=0; i<(1<<lv); ++i)
    {
        auto targ = make_pair(s - L[i].first, (uint64_t)0);
        auto it = lower_bound(R, R+(1<<rv), targ);
        
        if(it != (R+(1<<rv)) && it->first + L[i].first == s)
        {
            string x="";
            for(int j=lv-1; j>=0; --j)
            {
                if((L[i].second)&(1<<j)) x += "1";
                else x += "0";
            }
            for(int i=rv-1; i>=0; --i)
            {
                if((it->second)&(1<<i)) x += "1";
                else x += "0";
            }
            return x;
        }
    }
    //your mother's pie tastes bad.
    assert(false);
    return "??";
}
int main()
{
    cin >> N;
    for(int i=0; i<N; ++i)
        cin >> b[i];
    
    cin >> s;
    
    if(N<=20)
        cout << solve_naive() << endl;
    else
        cout << solve_inv() << endl;
    
    return 0;
}

string solve_small()
{
    if(N==1)
    {
        if(s==0) return "0";
        else return "1";
    }
    if(s==0) return "00";
    if(s==b[0]) return "10";
    if(s==b[1]) return "01";
    if(s==b[0]+b[1]) return "11";
}
