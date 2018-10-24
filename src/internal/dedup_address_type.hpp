//
//  dedup_address_type.hpp
//  blocksci
//
//  Created by Harry Kalodner on 3/7/18.
//

#ifndef dedup_address_type_hpp
#define dedup_address_type_hpp

#include <blocksci/blocksci_export.h>

#include <blocksci/core/meta.hpp>

#define DEDUP_ADDRESS_TYPE_LIST VAL(SCRIPTHASH), VAL(PUBKEY), VAL(MULTISIG), VAL(NULL_DATA), VAL(WITNESS_UNKNOWN), VAL(NONSTANDARD)
// DEDUP_ADDRESS_TYPE_SET is never used
#define DEDUP_ADDRESS_TYPE_SET VAL(SCRIPTHASH) VAL(PUBKEY) VAL(MULTISIG) VAL(NULL_DATA) VAL(WITNESS_UNKNOWN) VAL(NONSTANDARD)

namespace blocksci {

    struct DedupAddressType {
        
        enum Enum {
            // after preprocessing: NONSTANDARD, PUBKEY, SCRIPTHASH, MULTISIG, NULL_DATA, WITNESS_UNKNOWN
#define VAL(x) x
            DEDUP_ADDRESS_TYPE_LIST
#undef VAL
        };
        static constexpr size_t size = 6;

        // after preprocessing: using all = std::tuple<std::integral_constant<Enum, NONSTANDARD>, std::integral_constant<Enum, PUBKEY>, std::integral_constant<Enum, PUBKEYHASH>, std::integral_constant<Enum, MULTISIG_PUBKEY>, std::integral_constant<Enum, SCRIPTHASH>, std::integral_constant<Enum, MULTISIG>, std::integral_constant<Enum, NULL_DATA>, std::integral_constant<Enum, WITNESS_PUBKEYHASH>, std::integral_constant<Enum, WITNESS_SCRIPTHASH>, std::integral_constant<Enum, WITNESS_UNKNOWN> >;
        #define VAL(x) std::integral_constant<Enum, x>
        using all = std::tuple<DEDUP_ADDRESS_TYPE_LIST>;
        #undef VAL
        static constexpr Enum example = PUBKEY;

        /* after preprocessing:
         * static std::array<Enum,size> allArray() {
         *     return {{NONSTANDARD, PUBKEY, SCRIPTHASH, MULTISIG, NULL_DATA, WITNESS_UNKNOWN}};
         * }
         */
        #define VAL(x) x
        static std::array<Enum,size> allArray() {
            return {{DEDUP_ADDRESS_TYPE_LIST}};
        }
        #undef VAL
    };
    
    template <template<DedupAddressType::Enum> class K>
    using to_dedup_address_tuple_t = apply_template_t<DedupAddressType::Enum, K, DedupAddressType::all>;
}

namespace std {
    template<> struct hash<blocksci::DedupAddressType::Enum> {
        size_t operator()(blocksci::DedupAddressType::Enum val) const {
            return static_cast<size_t>(val);
        }
    };
}

#endif /* dedup_address_type_hpp */
