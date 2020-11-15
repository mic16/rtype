/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Compression
*/

#ifndef NETCOMPRESSION_HPP_
#define NETCOMPRESSION_HPP_

#include "boost/iostreams/filter/zlib.hpp"
#include "boost/iostreams/filter/gzip.hpp"
#include "boost/iostreams/filtering_streambuf.hpp"
#include "boost/iostreams/copy.hpp"
#include "boost/iostreams/stream_buffer.hpp"
#include "boost/iostreams/device/back_inserter.hpp"
#include <sstream>
#include <vector>

#include "lib/ByteBuffer/ByteBuffer.hpp"

class Compression {
    public:
        static void compress(ByteBuffer &in, ByteBuffer &out) {
            std::vector<char> compressed;
            boost::iostreams::array_source arr{reinterpret_cast<const char *>(in.flush()), in.getSize()};

            boost::iostreams::filtering_istreambuf os;
            os.push(boost::iostreams::zlib_compressor());
            os.push(arr);

            compressed.assign(std::istreambuf_iterator<char>{&os}, {});
            out.writeCharBuffer(compressed.data(), compressed.size());

            // std::cout << "Compress: " << compressed.size() << " " << in.getSize() << std::endl;
        }

        static void decompress(ByteBuffer &in, ByteBuffer &out) {
            int err = 0;
            size_t size = 0;
            char *data = in.readCharBuffer(&size, &err);

            if (err) {
                in.clear();
                return;
            }

            in.eat();

            std::vector<char> decompressed;
            boost::iostreams::array_source arr{data, size};

            // std::cout << "Try decompress: " << size << std::endl;

            try {
                boost::iostreams::filtering_istreambuf os;
                os.push(boost::iostreams::zlib_decompressor());
                os.push(arr);

                decompressed.assign(std::istreambuf_iterator<char>{&os}, {});
                out.append(decompressed.data(), decompressed.size());
            } catch (std::exception &e) {
                
            }

            delete []data;

            // std::cout << "Decompress: " << decompressed.size() << " " << size << std::endl;
        }

    protected:
    private:
};

#endif /* !NETCOMPRESSION_HPP_ */
