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

    BigInteger operator/(const BigInteger& o) {
        BigInteger res;
        BigInteger reminder(*this);
        int power = reminder.digits.size() - o.digits.size();
        if (power <= 0) {
            return 0;
        }
        res.digits.resize(power + 1, 0);
        while (reminder > o) {
            for (int d = 1; d <= 10; ++d) {
                BigInteger temp;
                temp.digits.resize(power,  0);
                temp.digits.push_back(d);
                if (temp * o > reminder) {
                    res.digits[power] = d - 1;
                    temp.digits[power] = d - 1;
                    reminder = reminder - temp * o;
                    power--;
                    break;
                }
            }
        }
        res.RemoveLeadingZeroes();
        return res;
    }

    BigInteger operator+(const BigInteger& o) {
        BigInteger res;
        res.digits.resize(std::max(digits.size(), o.digits.size()));
        for (int i = 0; i < res.digits.size(); ++i) {
            res.digits[i] = GetDigit(i) + o.GetDigit(i);
        }
        res.HandleCarry();
        return res;
    }

    BigInteger operator-(const BigInteger& o) {
        BigInteger res;
        res.digits.resize(std::max(digits.size(), o.digits.size()));
        for (int i = 0; i < res.digits.size(); ++i) {
            res.digits[i] = GetDigit(i) - o.GetDigit(i);
        }
        res.HandleNegativeCarry();
        res.RemoveLeadingZeroes();
        return res;
    }

    BigInteger operator*(const BigInteger& o) {
        BigInteger res;
        res.digits.resize(digits.size() + o.digits.size(), 0);
        for (int i = 0; i < digits.size(); ++i) {
            for (int j = 0; j < o.digits.size(); ++j) {
                res.digits[i + j] += digits[i] * o.digits[j];
            }
        }
        res.HandleCarry();
        res.RemoveLeadingZeroes();
        return res;
    }

    bool operator==(const BigInteger& o) const{
        if (o.digits.size() != digits.size())
            return false;
        for (int i = 0; i < digits.size(); ++i) {
            if (o.digits[i] != digits[i])
                return false;
        }
        return true;
    }

    bool operator!=(const BigInteger& o) const {
        return !(*this == o);
    }

    bool operator<(const BigInteger& o) const {
        if (digits.size() < o.digits.size())
            return true;
        if (digits.size() > o.digits.size())
            return false;

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] < o.digits[i])
                return true;
            if (digits[i] > o.digits[i])
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

    void HandleNegativeCarry() {
        // TODO: this function doesn't work for negative numbers
        for (int i = 0; i < digits.size(); ++i) {
            if (digits[i] < 0) {
                digits[i] += 10;
                digits[i + 1]--;
            }
        }
    }

    void RemoveLeadingZeroes() {
        while (digits.size() > 1 && digits[digits.size() - 1] == 0)
            digits.pop_back();
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
    std::cout << "SUBTRACTION TEST" << std::endl;
    BigInteger q = 1700;
    std::cout << q - 18 << std::endl;
    std::cout << "DIVISION TEST" << std::endl;
    BigInteger d = 1280;
    std::cout << d / 14 << std::endl;
}
