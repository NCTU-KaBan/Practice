# ION 題目

## Day1
- [x] A1: ~~小數點尾數被截掉 ex. 12.34 => 12.00 (ans的部分)~~
- [x] A2: ~~g/h 部份的公式 應該是 $b^2 - 4ac \over 4a^2$ 不是 $b^2 - 4ac \over 4a$~~
- [x] A3:
- [x] A4: 
- [x] A5:
- [x] A6: 
- [x] A7:
- [x] A8:

## Day2
- [x] B1: ~~題目敘述為輸出數字的index 但是測試資料是輸出數字的值~~
    - ~~大測資在OJ會MLE（標程）~~
- [x] B2:
- [x] B5:~~「5. 如果以上都一樣的話，越早出現的算式越麻煩」這個條件跟答案相反~~
    - 已改題目敘述
- [x] B7:
- [ ] C1:
- [x] C2:
- [x] C5:
- [x] C7:

## Day3
- [ ] C3: 1.in 的 S 超過1000
- [x] C4: local OK, oj不能傳
- [ ] C6:
- [x] C8: local OK, oj不能傳
- [x] E3: ~~output 尾巴多一個空白（不知道有沒有關係）, 2.in 300204行少一個數字~~
        - local OK, oj不能傳
- [ ] E4:
- [x] E6:
- [x] E8:

## Day4
- [ ] D1:
- [ ] D2:
- [ ] D3:
- [ ] D4:
- [ ] D5:
- [ ] D6:
- [ ] D7:
- [ ] D8:

## Day5
- [ ] B3:
- [ ] B4:    
    - (line 18)標程lower_bound前沒有先sort。
    - (line 24)判斷Yes or No的那個if的條件改為 query <= *it && *it - query <= 2 * S
    ```
    ----|......|------|.......|------------O----------- 數線
          區間        最後一個區間            ^
                              ^            |
                              |            |
                              it        query 的點

            *it - query 變成負值, 會導致*it - query <= 2 * S
    ```
    ```cpp=
    #include<vector>
    #include<iostream>
    #include <bits/stdc++.h>

    using namespace std;
    #define ll long long int

    int main()
    {
        ll N, M, S;
        cin >> N >> M >> S;
        vector<ll> pos(N);
        for(auto& it: pos)
        {
            cin >> it;
            it += S;
        }
        sort(pos.begin(), pos.end());
        for(int i = 0; i < M; i++)
        {
            ll query;
            cin >> query;
            auto it = lower_bound(pos.begin(), pos.end(), query);
            if(query <= *it && *it - query <= 2 * S)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
    ```
- [x] B6:
- [x] B8:
- [ ] E1:
- [ ] E2:
- [ ] E5:
- [ ] E7:
- [ ] E9:
- [ ] E10:
