#include <iostream>
#include <vector>

class BigInteger
{
public:
    BigInteger()
      : digits(1, 0)
    {}

    BigInteger(unsigned int x) {
        do {
            digits.push_back(x % 10);
            x /= 10;
        } while (x > 0);
    }

    BigInteger& operator++() {
        digits[0]++;
        HandleCarry();
        return *this;
    }

    BigInteger operator+(const BigInteger& o) {
        BigInteger res;
        res.digits.resize(std::max(this->digits.size(), o.digits.size()));
        for (int i = 0; i < res.digits.size(); ++i) {
            res.digits[i] = this->GetDigit(i) + o.GetDigit(i);
        }
        res.HandleCarry();
        return res;
    }

    bool operator==(const BigInteger& o) {
        if (o.digits.size() != this->digits.size())
            return false;
        for (int i = 0; i < this->digits.size(); ++i) {
            if (o.digits[i] != this->digits[i])
                return false;
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInteger& num);
private:
    void HandleCarry() {
        for (int i = 0; i < digits.size(); ++i) {
            int carry = digits[i] / 10;
            digits[i] %= 10;
            if (i == digits.size() - 1 && carry != 0) {
                digits.push_back(carry);
            } else {
                digits[i + 1] += carry;
            }
        }
    }

    int GetDigit(int idx) const {
        if (idx < 0)
            throw std::exception(); // TODO
        if (idx > digits.size() - 1)
            return 0;
        return digits[idx];
    }
    // Digits in base 10
    // TODO: It is not very memory/cpu efficient
    // Little-Endian-ish
    std::vector<int> digits;
};

std::ostream& operator<<(std::ostream& out, const BigInteger& num){
   for (int i = num.digits.size() - 1; i >= 0; --i) {
       out << num.digits[i];
    }
   return out;
}

int main()
{
    BigInteger x = 1000000000;
    BigInteger y = 1000000000;
    std::cout << x << " " << y << std::endl;
    BigInteger z = x + y;
    std::cout << z << std::endl;
    BigInteger a = z + x + y;
    std::cout << a << std::endl;
}
