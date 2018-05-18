#if !defined(HANDLE_H)

namespace core {

    struct CORE_API Handle {
    private:
        struct handle_data_t {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        union handle_t {
            struct handle_data_t data;
            uint64_t value;
        };

        handle_t handle;
    public:
        Handle();
        Handle( uint32_t index );
        Handle( uint64_t value );
        void set_index( uint32_t new_index );
        void increment_phase();
        bool is_active();
        void set_active();
        void set_inactive();
        uint32_t get_index();
        uint64_t get_value();

        operator uint64_t() const;
        void operator = ( const uint64_t &value );
    };

} // end namespace core

#define HANDLE_H
#endif
