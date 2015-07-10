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

    BigInteger operator++(int) {
        BigInteger copy(*this);
        ++copy;
        return copy;
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

    BigInteger operator*(const BigInteger& o) {
        BigInteger res;
        res.digits.resize(this->digits.size() + o.digits.size(), 0);
        for (int i = 0; i < this->digits.size(); ++i) {
            for (int j = 0; j < o.digits.size(); ++j) {
                res.digits[i + j] += this->digits[i] * o.digits[j];
            }
        }
        res.HandleCarry();
        res.RemoveLeadingZeroes();
        return res;
    }

    bool operator==(const BigInteger& o) const{
        if (o.digits.size() != this->digits.size())
            return false;
        for (int i = 0; i < this->digits.size(); ++i) {
            if (o.digits[i] != this->digits[i])
                return false;
        }
        return true;
    }

    bool operator!=(const BigInteger& o) const {
        return !(*this == o);
    }

    bool operator<(const BigInteger& o) const {
        if (this->digits.size() < o.digits.size())
            return true;
        if (this->digits.size() > o.digits.size())
            return false;

        for (int i = this->digits.size() - 1; i >= 0; --i) {
            if (this->digits[i] < o.digits[i])
                return true;
            if (this->digits[i] > o.digits[i])
                return false;
        }
        return false;
    }

    bool operator<=(const BigInteger& o) const{
        return *this < o || *this == o;
    }

    bool operator>(const BigInteger& o) const{
        return o < *this;
    }

    bool operator>=(const BigInteger& o) const{
        return o <= *this;
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

    void RemoveLeadingZeroes() {
        while (this->digits.size() > 1 && this->digits[this->digits.size() - 1] == 0)
            this->digits.pop_back();
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
    std::cout << (z == 42) << std::endl;
    std::cout << "NON-EQ test" << std::endl;
    std::cout << (z != 42) << std::endl;
    std::cout << "NON-EQ test ended" << std::endl;
    std::cout << (z < 42) << std::endl;
    std::cout << "TEST" << std::endl;
    std::cout << (z + z + 1 < z + z + 2) << std::endl;
}
