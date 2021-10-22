#include <iostream>
#include <chrono>
#include <list>
#include "SHA256.h"
#include "Sha256.h"
#include <unistd.h>
#include <string>
#include <vector>
#include <climits>
#include <random>
#include <algorithm>
#include <functional>

/*      =====       NOTE: THIS IS INNACURATE AND MOSTLY EXPERIMENTAL        =====      */

class calcHashRate
{
    public:
        void hashRate()
        {
            std::list<std::string>HashList;
            std::list<std::string>::iterator it;
            auto start = std::chrono::system_clock::now();
            auto end_t = std::chrono::system_clock::now();
            do
            {
                // random bytes generated!
                using random_bytes_engine = std::independent_bits_engine
                                            <std::default_random_engine,CHAR_BIT,unsigned char>;
                random_bytes_engine rbe;
                std::vector<unsigned char> data(1000);
                std::generate(data.begin(),data.end(),std::ref(rbe));
                for (int c=0;c<data.size();c++)
                {
                    std::string calc = sha256(std::to_string(data[c])); // hash byte_r
                    auto it = HashList.begin();
                    HashList.insert(it, calc);
                    std::cout << calc; /* without output it's f'ed up */

                }
                end_t = std::chrono::system_clock::now();
            } while (std::chrono::duration_cast<std::chrono::seconds>
                    (end_t - start).count() != 1);
            std::cout << std::endl << std::endl << "Hashrate = " << HashList.size();
        }
};

int main()
{
    calcHashRate hash;
    hash.hashRate();
    return 0;
}
