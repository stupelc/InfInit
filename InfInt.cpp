/*********************************
 * Studrnt name : Chagit Stupel
 * Student ID: 209089960
 * Course exercise group: 89210-06
 * Exercise name : ex1
 *********************************/

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#include "LargeIntegers.h"

/**
 * the default constructor
 */
InfInt::InfInt() {
    this->x = "0";
    this->len = 0;
    if (this->x[0] == '-') {
        this->isNeg = true;
    }
}

/**
 * @param str - a string number
 * a constructor that gets a string and update the details of infinit
 */
InfInt::InfInt(const string str) {
    this->isNeg = IsTheNumNeg(str);
    if (isNeg) {
        this->x = ConvertToBinary(str.substr(1, str.length()));
    } else
        this->x = ConvertToBinary(str);
    this->len = this->x.length();
    if (this->x.length() == 0) {
        this->x = "0";
    }
}

/**
 * @param n - an int number
 * a constructor that gets an int and update the details of infinit
 */
InfInt::InfInt(int n) {
    string newStr;
    newStr = to_string(n);

    if (n < 0) {
        this->isNeg = true;
        this->x = newStr.substr(1, newStr.length());
    } else {
        this->isNeg = false;
        this->x = newStr;
    }
    this->x = ConvertToBinary(newStr);
    this->len = this->x.length();
}

/**
 * @param n a long number
 *  a constructor that gets a long and update the details of infinit
 */
InfInt::InfInt(long n) {
    string newStr;
    newStr = to_string(n);

    if (n < 0) {
        this->isNeg = true;
        this->x = newStr.substr(1, newStr.length());
    } else {
        this->isNeg = false;
        this->x = newStr;
    }
    this->x = ConvertToBinary(newStr);
    this->len = this->x.length();
}

/**
 * @param num2 an infint const number
 * @return the result of (+) between 2 numbers
 */
InfInt InfInt::operator+(const InfInt num2) const {

    InfInt thisInf = *this;
    InfInt infInt2 = num2;

    InfInt check("0");
    if (infInt2.isNeg) {
        check.x = infInt2.x;
        check.len = check.x.length();
    } else {
        check.x = thisInf.x;
        check.len = check.x.length();
    }

    //(+)this + (-)infinity2 = (-)result
    if (infInt2.isNeg && !thisInf.isNeg && (check.operator>(thisInf))) {
        InfInt result = thisInf.operator-(check);
        result.len = result.x.length();
        result.isNeg = true;
        return result;
    }
    //(+)this + (-)infinity2 = (+)result
    if (infInt2.isNeg && !thisInf.isNeg && (check.operator<(thisInf))) {
        InfInt result = thisInf.operator-(infInt2);
        result.len = result.x.length();
        result.isNeg = false;
        return result;
    }
    //(-)this + (+)infinity2 = (-)result
    if (!infInt2.isNeg && thisInf.isNeg && (check.operator>(infInt2))) {
        InfInt result = check.operator-(infInt2);
        result.len = result.x.length();
        result.isNeg = true;
        return result;
    }
    //(-)this + (+)infinity2 = (+)result
    if (!infInt2.isNeg && thisInf.isNeg && (check.operator<(infInt2))) {
        InfInt result = infInt2.operator-(check);
        result.len = result.x.length();
        result.isNeg = false;
        return result;
    }
    //(-)this + (-)infinity2 = (-)result
    if (thisInf.isNeg && infInt2.isNeg) {
        InfInt newInfInt1("0");
        InfInt newInfInt2("0");

        newInfInt1.x = thisInf.x;
        newInfInt2.x = infInt2.x;

        InfInt result = newInfInt1.operator+(newInfInt2);
        result.len = result.x.length();
        result.isNeg = true;
        return result;
    }
    // we make sure length of the string2 we get is larger.
    if ((thisInf.x.length() > infInt2.x.length()))
        swap(thisInf.x, infInt2.x);

    // Take an empty string for storing result
    string str = "";

    // Calculate lenght of both string
    int n1 = thisInf.x.length(), n2 = infInt2.x.length();

    // Reverse both of strings
    reverse(thisInf.x.begin(), thisInf.x.end());
    reverse(infInt2.x.begin(), infInt2.x.end());

    int carry = 0;
    for (int i = 0; i < n1; i++) {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((thisInf.x[i] - '0') + (infInt2.x[i] - '0') + carry);
        str.push_back(sum % 2 + '0');

        // Calculate carry for next step
        carry = sum / 2;
    }

    // Add remaining digits of larger number
    for (int i = n1; i < n2; i++) {
        int sum = ((infInt2.x[i] - '0') + carry);
        str.push_back(sum % 2 + '0');
        carry = sum / 2;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry + '0');

    // reverse resultant string
    reverse(str.begin(), str.end());

    int i = 0;
    while (str[i] == '0') {
        i++;
    }
    str = str.substr(i, str.length());

    if (str.size() == 0) {
        str = "0";
    }

    //convert the string to infi number
    InfInt infi;
    //both of the numbers were positive so the answer will be positive too
    if (!thisInf.isNeg && !infInt2.isNeg)
        infi.isNeg = false;
    infi.setNum(str);
    infi.len = infi.x.length();

    return infi;
}

/**
 * @param num2 an infint const number
 * @return the result of (-) between 2 numbers
 */
InfInt InfInt::operator-(const InfInt num2) const {

    InfInt thisInf = *this;
    InfInt infInt2 = num2;

    InfInt result;
    InfInt check1("0");
    if (infInt2.isNeg) {
        check1.x = infInt2.x;
        check1.len = check1.x.length();
    } else {
        check1.x = thisInf.x;
        check1.len = check1.x.length();
    }

    InfInt check2("0");
    check2.x = thisInf.x;
    check2.len = check2.x.length();

    //(-)this - (-)infinity2 = ()result (this<infinity2)
    if (thisInf.isNeg && infInt2.isNeg && check2.operator<(check1)) {
        result = check1.operator-(check2);
        result.isNeg = false;
        return result;
    }

    //(-)this - (-)infinity2 = ()result (this>infinity2)
    if (thisInf.isNeg && infInt2.isNeg && check2.operator>(check1)) {
        result = check1.operator-(check2);
        result.isNeg = true;
        return result;
    }

    //(+)this - (-)infinity2 = (-)result
    if (!thisInf.isNeg && infInt2.isNeg) {
        result = check1.operator+(thisInf);
        result.isNeg = false;
        return result;
    }

    //(-)this - (+)infinity2 = (-)result : the regular colculation
    if (thisInf.isNeg && !infInt2.isNeg && thisInf.operator<(infInt2)) {
        result = check1.operator+(infInt2);
        result.isNeg = true;
        return result;
    }

    //(+)this - (+)infinity2 = (+)result (this>infinity2)
    if (!thisInf.isNeg && !infInt2.isNeg && thisInf.operator>(infInt2)) {
        result.isNeg = false;
    }

    //(+)this - (+)infinity2 = ()result (this<infinity2)
    if (!thisInf.isNeg && !infInt2.isNeg && thisInf.operator<(infInt2)) {
        result = infInt2.operator-(thisInf);
        result.isNeg = true;
        return result;
    }

    // Before proceeding further, make sure str1
    // is not smaller
    if (thisInf.len < infInt2.len)
        swap(thisInf.x, infInt2.x);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = thisInf.len, n2 = infInt2.len;

    // Reverse both of strings
    reverse(thisInf.x.begin(), thisInf.x.end());
    reverse(infInt2.x.begin(), infInt2.x.end());

    int carry = 0;

    // Run loop till small string length
    // and subtract digit of str1 to str2
    for (int i = 0; i < n2; i++) {
        // Do school mathematics, compute difference of
        // current digits

        int sub = ((thisInf.x[i] - '0') - (infInt2.x[i] - '0') - carry);

        // If subtraction is less then zero
        // we add then we add 10 into sub and
        // take carry as 1 for calculating next step
        if (sub < 0) {
            sub = sub + 2;
            carry = 1;
        } else
            carry = 0;

        str.push_back(sub + '0');
    }

    // subtract remaining digits of larger number
    for (int i = n2; i < n1; i++) {
        int sub = ((thisInf.x[i] - '0') - carry);

        // if the sub value is -ve, then make it positive
        if (sub < 0) {
            sub = sub + 2;
            carry = 1;
        } else
            carry = 0;

        str.push_back(sub + '0');
    }

    // reverse resultant string
    reverse(str.begin(), str.end());

    int i = 0;
    while (str[i] == '0') {
        i++;
    }
    str = str.substr(i, str.length());
    if (str.size() == 0) {
        str = "0";
    }
    result.setNum(str);
    result.isNeg = false;
    result.len = result.x.length();
    return result;
}

/**
 * @param infInt2 an infint const number
 * @return 1 - if the 'this' number is less than 'infinit2' number
 *         0 - otherwise
 */
bool InfInt::operator<(const InfInt infInt2) const {

    //check the sigh in the 2 numbers
    if (this->isNeg && !infInt2.isNeg) { //the first (-) the second (+)
        return true;
    } else if (!this->isNeg && infInt2.isNeg) {//the first (+) the second (-)
        return false;
    }
    //both of them in the same sign (+)
    if (!this->isNeg && !infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return true;
        else if (this->x.length() > infInt2.x.length()) return false;
        //both of them in the same sign (-)
    } else if (this->isNeg && infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return false;
        else if (this->x.length() > infInt2.x.length()) return true;
    }
    if (this->x.length() == infInt2.x.length()) {
        //now we will run on the number and check who is bigger
        int i = 0;
        while (i <= this->x.length() - 1) {
            if (this->x[i] == infInt2.x[i])i++;
            else if (this->x[i] > infInt2.x[i])return false;
            else return true;
        }
    }
    //if we got here the numbers were equals so no one of them is smaller thsn the other
    return false;
}

/**
 * @param infInt2 an infint const number
 * @return 1 - if the 'this' number is more than 'infinit2' number
 *         0 - otherwise
 */
bool InfInt::operator>(const InfInt infInt2) const {

    //check the sigh in the 2 numbers
    if (this->isNeg && !infInt2.isNeg) { //the first (-) the second (+)
        return false;
    } else if (!this->isNeg && infInt2.isNeg) {//the first (+) the second (-)
        return true;
    }
    //both of them in the same sign (+)
    if (!this->isNeg && !infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return false;
        else if (this->x.length() > infInt2.x.length()) return true;
        //both of them in the same sign (-)
    } else if (this->isNeg && infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return true;
        else if (this->x.length() > infInt2.x.length()) return false;
    }
    if (this->x.length() == infInt2.x.length()) {
        //now we will run on the number and check who is bigger
        int i = 0;
        while (i <= this->x.length() - 1) {
            if (this->x[i] == infInt2.x[i])i++;
            else if (this->x[i] > infInt2.x[i])return true;
            else return false;
        }
    }
    //if we got here the numbers were equals so no one of them is smaller thsn the other
    return false;
}

/**
 * @param infInt2 an infint const number
 * @return 1 - if the 'this' number is equal to 'infinit2' number
 *         0 - otherwise
 */
bool InfInt::operator==(const InfInt infInt2) const {

    //check the sigh and the length of the numbers
    if ((this->isNeg && !infInt2.isNeg) || (!this->isNeg && infInt2.isNeg) ||
        (this->x.length() != infInt2.x.length()))
        return false;
    else {
        //now we will run on the number and check if there are equals
        int i = 0;
        while (i <= this->x.length() - 1) {
            if (this->x[i] != infInt2.x[i])
                return false;
            i++;
        }
    }
    return true;
}

/**
 * @param infInt2 an infint const number
 * @return 1 - if the 'this' number is less than 'infinit2' number or equal to him
 *         0 - otherwise
 */
bool InfInt::operator<=(const InfInt infInt2) const {

    //check the sigh in the 2 numbers
    if (this->isNeg && !infInt2.isNeg) { //the first (-) the second (+)
        return true;
    } else if (!this->isNeg && infInt2.isNeg) {//the first (+) the second (-)
        return false;
    }
    //both of them in the same sign (+)
    if (!this->isNeg && !infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return true;
        else if (this->x.length() > infInt2.x.length()) return false;
        //both of them in the same sign (-)
    } else if (this->isNeg && infInt2.isNeg) {
        if (this->x.length() < infInt2.x.length()) return false;
        else if (this->x.length() > infInt2.x.length()) return true;
    }
    if (this->x.length() == infInt2.x.length()) {
        //now we will run on the number and check who is bigger
        int i = 0;
        while (i <= this->x.length() - 1) {
            if (this->x[i] == infInt2.x[i])i++;
            else if (this->x[i] > infInt2.x[i])return false;
            else return true;
        }
    }
    //if we got here the numbers were equals so no one of them is smaller thsn the other
    return true;
}

/**
* @param infInt2 an infint const number
* @return 1 - if the 'this' number is more than 'infinit2' number or equal to him
*         0 - otherwise
*/
bool InfInt::operator>=(const InfInt num2) const {

    InfInt thisInf = *this;
    InfInt infInt2 = num2;

    //check the sigh in the 2 numbers
    if (this->isNeg && !infInt2.isNeg) { //the first (-) the second (+)
        return false;
    } else if (!this->isNeg && infInt2.isNeg) {//the first (+) the second (-)
        return true;
    }

    int len1 = thisInf.x.length();
    int len2 = infInt2.x.length();
    if (len1 > len2) {
        int remind = len1 - len2;
        for (int i = 1; i <= remind; i++) {
            infInt2.x = '0' + infInt2.x;
        }
    } else if (len1 < len2) {
        int remind = len2 - len1;
        for (int i = 1; i <= remind; i++) {
            thisInf.x = '0' + thisInf.x;
        }
    }

    if (thisInf.x.length() == infInt2.x.length()) {
        //now we will run on the number and check who is bigger
        int i = 0;
        while (i <= thisInf.x.length() - 1) {
            if (thisInf.x[i] == infInt2.x[i])i++;
            else if (thisInf.x[i] > infInt2.x[i])return true;
            else return false;
        }
    }
    //if we got here the numbers were equals so no one of them is smaller thsn the other
    return true;
}

/**
 * @param infInt2 an infint const number
 * @return the result of (&) between 2 numbers
 */
InfInt InfInt::operator&(const InfInt infInt2) const {

    string newStr = "";
    string big = this->x;
    string small = infInt2.x;
    int len = max(this->x.length(), infInt2.x.length());
    int minLen = min(this->x.length(), infInt2.x.length());

    if (this->x.length() != infInt2.x.length()) {
        //we decide the len of the bigger number
        if (this->x.length() > infInt2.x.length()) {
            big = this->x;
            small = infInt2.x;
        } else {
            big = infInt2.x;
            small = this->x;
        }

        //add 0 to thet small number
        for (int i = len - minLen - 1; i >= 0; i--) {
            small = '0' + small;
        }
    }
    for (int i = len - 1; i >= 0; i--) {
        if (big[i] == '1' && small[i] == '1') {
            newStr = '1' + newStr;
        } else {
            newStr = '0' + newStr;
        }
    }

    //deleate the '0' that we don't need
    int i = 0;
    while (newStr[i] == '0') {
        i++;
    }
    newStr = newStr.substr(i, newStr.length());
    if (newStr.size() == 0) {
        newStr = "0";
    }
    InfInt infi;
    infi.setNum(newStr);
    if ((this->isNeg && !infInt2.isNeg) || (!this->isNeg && infInt2.isNeg))
        infi.isNeg = true;
    else
        infi.isNeg = false;
    infi.len = infi.x.length();

    return infi;
}

/**
 * @param infInt2 an infint const number
 * @return the result of (|) between 2 numbers
 */
InfInt InfInt::operator|(const InfInt infInt2) const {

    string newStr = "";
    string big = this->x;
    string small = infInt2.x;
    int len = max(this->x.length(), infInt2.x.length());
    int minLen = min(this->x.length(), infInt2.x.length());

    if (this->x.length() != infInt2.x.length()) {
        //we decide the len of the bigger number
        if (this->x.length() > infInt2.x.length()) {
            big = this->x;
            small = infInt2.x;
        } else {
            big = infInt2.x;
            small = this->x;
        }

        //add 0 to thet small number
        for (int i = len - minLen - 1; i >= 0; i--) {
            small = '0' + small;
        }
    }
    for (int i = len - 1; i >= 0; i--) {
        if (big[i] == '1' || small[i] == '1') {
            newStr = '1' + newStr;
        } else {
            newStr = '0' + newStr;
        }
    }

    //deleate the '0' that we don't need
    int i = 0;
    while (newStr[i] == '0') {
        i++;
    }
    newStr = newStr.substr(i, newStr.length());
    if (newStr.size() == 0) {
        newStr = "0";
    }
    InfInt infi;
    infi.setNum(newStr);
    //todo check if the if is correct
    if ((!this->isNeg || !infInt2.isNeg))
        infi.isNeg = false;
    else
        infi.isNeg = true;
    infi.len = infi.x.length();

    return infi;
}

/**
 * @param infInt2 an infint const number
 * @return the result of (^) between 2 numbers
 */
InfInt InfInt::operator^(const InfInt infInt2) const {

    string newStr = "";
    string big = this->x;
    string small = infInt2.x;
    int len = max(this->x.length(), infInt2.x.length());
    int minLen = min(this->x.length(), infInt2.x.length());

    if (this->x.length() != infInt2.x.length()) {
        //we decide the len of the bigger number
        if (this->x.length() > infInt2.x.length()) {
            big = this->x;
            small = infInt2.x;
        } else {
            big = infInt2.x;
            small = this->x;
        }

        //add 0 to thet small number
        for (int i = len - minLen - 1; i >= 0; i--) {
            small = '0' + small;
        }
    }
    for (int i = len - 1; i >= 0; i--) {
        if ((big[i] == '1' && small[i] == '0') || (big[i] == '0' && small[i] == '1')) {
            newStr = '1' + newStr;
        } else {
            newStr = '0' + newStr;
        }
    }

    //deleate the '0' that we don't need
    int i = 0;
    while (newStr[i] == '0') {
        i++;
    }
    newStr = newStr.substr(i, newStr.length());
    if (newStr.size() == 0) {
        newStr = "0";
    }
    InfInt infi;
    infi.setNum(newStr);
    //todo check if the if is correct
    if ((!this->isNeg && !infInt2.isNeg) || (this->isNeg && infInt2.isNeg))
        infi.isNeg = false;
    else
        infi.isNeg = true;
    infi.len = infi.x.length();

    return infi;
}

/**
 * @param infInt2 an infint const number
 * @return the result of (&) between 2 numbers and change the 'this' number
 */
InfInt &InfInt::operator&=(const InfInt infInt2) {
    //by using the operator (&) we are updating the number
    InfInt infInt = infInt2.operator&(*this);
    this->x = infInt.x;
    this->len = infInt.len;
    return *this;
}

/**
 * @param infInt2 an infint const number
 * @return the result of (+) between 2 numbers and change the 'this' number
 */
InfInt &InfInt::operator+=(const InfInt infInt2) {
    //by using the operator (+) we are updating the number
    InfInt infInt = infInt2.operator+(*this);
    this->x = infInt.x;
    this->len = infInt.len;
    return *this;
}

/**
 * @return the new infinit number.
 * add 1 to then number (postfix)
 */
InfInt &InfInt::operator++() {
    InfInt infInt("1");
    *this = *this + (infInt);
    return *this;
}

/**
 * @return the new infinit number.
 * add 1 to then number (prefix)
 */
InfInt InfInt::operator++(int num) {
    //keep the value before the adding in a temp variable and return it
    InfInt temp(0);
    temp = *this;
    ++(*this);
    return temp;
}

/**
 * @return the new infinit number.
 * subtract 1 to then number (postfix)
 */
InfInt &InfInt::operator--() {
    InfInt infInt("1");
    *this = *this - (infInt);
    return *this;
}

/**
 * @return the new infinit number.
 * subtract 1 to then number (prefix)
 */
InfInt InfInt::operator--(int num) {
    //keep the value before the adding in a temp variable and return it
    InfInt temp("0");
    temp = *this;
    --(*this);
    return temp;
}

/**
* @param num2 an infint const number
* @return the result of (*) between 2 numbers
*/
InfInt InfInt::operator*(const InfInt num2) const {

    //make a new changes to the original variables
    InfInt thisInf = *this;
    InfInt infInt2 = num2;

    int n1 = thisInf.len;
    int n2 = infInt2.len;
    if (n1 == 0 || n2 == 0)
        return InfInt("0");

    // will keep the result number in vector in reverse order
    vector<int> result(n1 + n2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = thisInf.x[i] - '0';

        // To shift position to left after every multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (int j = n2 - 1; j >= 0; j--) {
            // Take current digit of second number
            int n2 = infInt2.x[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 2;

            // Store result
            result[i_n1 + i_n2] = sum % 2;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // If all were '0's - means either both or one of num1 or num2 were '0'
    if (i == -1)
        return InfInt("0");

    // generate the result string
    string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    //convert the string to infi number and update the data
    InfInt infi;
    if ((thisInf.isNeg && !infInt2.isNeg) || (!thisInf.isNeg && infInt2.isNeg))
        infi.isNeg = true;
    else
        infi.isNeg = false;
    infi.setNum(s);
    infi.len = infi.x.length();
    return infi;
}

/**
 * @param str - a string
 * set the number according to the string
 */
void InfInt::setNum(string str) {
    this->x = str;
}

/**
 * @param num2 an infint number
 * @param task if the task is 1 - do '/'
 *             if the task is 0 - do '%'
 * @return the result of the mission the user choose
 */
InfInt InfInt::devide(const InfInt num2, int task) const {

    //keep our variables in a new variables
    InfInt thisInf = *this;
    InfInt infInt2 = num2;

    bool ansSigh = false;
    //check the sigh of the answer
    if ((thisInf.isNeg && !infInt2.isNeg) || (!thisInf.isNeg && infInt2.isNeg)) {
        ansSigh = true;
    }

    InfInt zeroInf;
    if (infInt2.x == "0")
        __throw_bad_exception();

    // if the number we wanna to devide with is 1 we will return the number without changes
    if (infInt2.x == "1") {
        thisInf.isNeg = ansSigh;
        return thisInf;
    }

    thisInf.isNeg = false;
    infInt2.isNeg = false;

    InfInt r, q;
    q.isNeg = false;
    r.isNeg = false;
    string zero = "";
    int size = 0;
    size = max(thisInf.x.size(), infInt2.x.size());
    for (int i = 0; i < size; i++) {
        zero += '0';
    }
    q.setNum(zero);
    for (int i = 0; i < thisInf.x.size(); i++) {
        r <<= 1;
        r.x[r.x.size() - 1] = (thisInf.x)[i];
        if (r >= infInt2) {
            r = r - infInt2;
            q.x[i] = '1';
        }
    }

    int i = 0;
    while (r.x[i] == '0') {
        i++;
    }
    r.x = r.x.substr(i, r.x.length());
    if (r.x.size() == 0) {
        r.x = "0";
    }

    i = 0;
    while (q.x[i] == '0') {
        i++;
    }
    q.x = q.x.substr(i, q.x.length());

    if (q.x.size() == 0) {
        q.x = "0";
        ansSigh = false;
        q.len = q.x.length();
    }

    // if the task is 1 we will return the value of q which presented the whole from the devide
    if (task == 1) {
        q.isNeg = ansSigh;
        return q;
        // if the task is 0 we will return the value of r which presented the rest from the devide
    } else {
        r.isNeg = false;
        return r;
    }
}

/**
* @param infInt2 an infint const number
* @return the result of (/) between 2 numbers
*/
InfInt InfInt::operator/(const InfInt infInt2) const {
    return devide(infInt2, 1);
}

/**
* @param infInt2 an infint const number
* @return the result of (%) between 2 numbers
*/
InfInt InfInt::operator%(const InfInt infInt2) const {
    return devide(infInt2, 0);
}

/**
 * @param move the number of moves that we wanna do on the number
 * @return the result of (<<) on a number according to the number the user decide
 */
InfInt InfInt::operator<<(int move) const {
    InfInt newInfint;
    newInfint = *this;

    //in those cases we d'ont wanna do nothing
    if (move < 0 || newInfint.x == "0") {
        return newInfint;
    }

    for (int i = 0; i <= move - 1; i++) {
        newInfint.x = newInfint.x + "0";
    }

    //both of the numbers were positive so the answer will be positive too
    if (this->isNeg)
        newInfint.isNeg = true;
    newInfint.len = newInfint.x.length();

    return newInfint;
}

/**
 * @param move the number of moves that we wanna do on the number
 * @return the result of (>>) on a number according to the number the user decide
 */
InfInt InfInt::operator>>(int move) const {
    InfInt newInfint;
    newInfint = *this;
    //in those cases we d'ont wanna do nothing
    if (move < 0 || newInfint.x == "0") {
        newInfint.len = newInfint.x.length();
        return newInfint;
    }

    //cant do a shift when the num of move is bigger than the num of the bits
    if (move >= this->x.length())
        return InfInt("0");

    //we will cut the number according to the num of move
    newInfint.x = newInfint.x.substr(0, newInfint.x.length() - move);
    if (newInfint.x.size() == 0) {
        newInfint.x = "0";
    }
    if (this->isNeg)
        newInfint.isNeg = true;
    newInfint.len = newInfint.x.length();

    return newInfint;
}

/**
 * @param move the number of moves that we wanna do on the number
 * @return the result of (<<=) on a number according to the number the user decide
 *                                                       and update the number
 */
InfInt &InfInt::operator<<=(int move) {
    *this = *this << (move);
    return *this;
}

/**
 * @param move the number of moves that we wanna do on the number
 * @return the result of (>>=) on a number according to the number the user decide
 *                                                       and update the number
 */
InfInt &InfInt::operator>>=(int move) {
    *this = *this >> (move);
    return *this;
}

/**
 * @return an int number
 * convert a number from infint to int by taking the 32 right bits
 */
InfInt::operator int() const {
    //we cast the number to get it in bits
    InfInt thisInf = *this;

    //if the length of the number is more that 32 bits we wanna to cut it
    if (thisInf.len > 32) {
        //cut the first 32 bits
        thisInf.x = thisInf.x.substr(thisInf.len - 32, thisInf.len - 1);
        thisInf.len = thisInf.x.length();
    }

    //cast the number to int number
    unsigned int j = 0, count = 0;
    for (int i = 0; i <= (thisInf.x.length() - 1); i++) {
        if (thisInf.x[i] == '1') {
            j = j + pow(2, (thisInf.x.length() - i - 1));
        }
        count++;
    }

    //if the number is neg we will mult in -1
    if (thisInf.isNeg) {
        j *= (-1);
    }

    //update the data
    thisInf.len = thisInf.x.length();
    return j;
}

/**
 * @param str a string
 * @return true if the number is negative
 *        and false if the number is positive
 */
bool InfInt::IsTheNumNeg(string str) const {
    if (str[0] == '-') {
        return true;
    }
    return false;
}

/**
 * @param number - string number
 * @return the string representation as a binary number
 */
string InfInt::ConvertToBinary(string number) {
    string numberTempString = "";
    string afterDiv = "";
    int index = 0;
    int digit = 0;
    long i = 0;
    int tempDiv = 0;
    string binaryNum = "";
    //index = !s.compare("0");
    // if the number is negative
    if (number[0] == '-') {
        i++;
    }

    while (number.compare("0")) {
        if (number[0] - 48 == 0) {
            i++;
        }
        for (i; i < number.size(); i++) {
            if ((number[i] >= '0') && (number[i] <= '9')) {
                digit = number[i] - '0';
                if (i == number.size() - 1) {
                    if (digit % 2) {
                        binaryNum += '1';
                    } else {
                        binaryNum += '0';
                    }
                }

                if (digit % 2 == 0) {
                    digit = digit / 2 + tempDiv + 48;
                    afterDiv += digit;
                    tempDiv = 0;
                } else {
                    digit = digit / 2 + tempDiv + 48;
                    afterDiv += digit;
                    tempDiv = 5;
                }
            } else {
                return NULL;
            }
        }
        number = afterDiv;
        tempDiv = 0;
        afterDiv = "";
        i = 0;
    }
    std::reverse(binaryNum.begin(), binaryNum.end());
    return binaryNum;

}

/**
 * @param inf - infint number
 * @return the string representation as a decimal number (in the regular way)
 */
string InfInt::ConvertToDecimal(InfInt inf) {
    if (inf.x == "0") {
        return "0";
    }

    //keep the sigh that will have to the funal answer
    bool sighAns = inf.isNeg;

    InfInt infint;
    InfInt ten("10");
    string dec;
    int integer;
    //while the number isnt 0 we wanna to devide and number and keep the rest
    while (inf.x != "0") {
        infint = inf % ten;
        integer = (int) infint;
        dec += to_string(integer);
        inf = inf / ten;
    }
    reverse(dec.begin(), dec.end());
    if (sighAns) {
        dec = "-" + dec;
    }
    return dec;

}

/**
 * @param out - a ostream
 * @param infint an infint number
 * @return an output function
 */
ostream &operator<<(ostream &out, InfInt infint) {
    //transfor the number from a binary represetion to a decimal represetion
    string s = infint.ConvertToDecimal(infint);
    out << s;
    return out;
}

/**
 * @param out - a ostream
 * @param infint an infint number
 * @return an input function
 */
istream &operator>>(istream &in, InfInt &infint) {
    in >> infint.x;
    infint = InfInt(infint.x);
    return in;
}