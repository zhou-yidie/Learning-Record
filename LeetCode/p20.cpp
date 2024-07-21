class Solution {
public:
    stack< char > st;

    bool check( char tmp ) {
        char pre = st.top();
        st.pop();
        if (tmp == ')' && pre == '(') {
            
            return true;
        }
        if (tmp == ']' && pre == '[') {
            return true;
        }
        if (tmp == '}' && pre == '{') {
            return true;
        }
        return false;
    }
    bool isValid(string s) {
        for (int i = 0 ; i < s.size() ; i++ ) {
            if ( s[i] == ')' || s[i] == '}' || s[i] == ']' ) {
                if ( st.size() == 0 || !check(s[i]) ) {
                    return false;
                } 
            } else {
                st.push(s[i]);
            }
        }
        return st.size() == 0 ;
    }
};
