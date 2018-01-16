/*
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

*/

/*
Compute the ones-digit, then the tens-digit, then the hundreds-digit, etc.
For example when multiplying 1234 with 5678, the thousands-digit of the 
product is 4\*5 + 3\*6 + 2\*7 + 1\*8 (plus what got carried from the hundreds-digit).
*/

string multiply(string a, string b) {
    if (a=="0" || b=="0")
        return "0";
    int m = a.size() - 1;
    int n = b.size() - 1;
    int carry = 0;
    string product;
    int total_digits = m + n;
    for (int i = 0; i <= total_digits || carry; ++i) {
        int j = max(0, i-n);
        while(j <= min(i, m)) {
            carry += (a[m-j] - '0') * (b[n-i+j] - '0');
            j++;
        }
        product += carry % 10 + '0';
        carry /= 10;
    }
    reverse(product.begin(), product.end());
    return product;
}


