// Given to the Public Domain by Pyarelal Knowles under CC0 1.0 Universal

#pragma once

#if __has_include(<ranges>)
#include <ranges>
#endif

namespace container_boilerplate {

template <class T>
class my_value_reference {
public:
    using value_type = T;

    my_value_reference() = delete;
    my_value_reference& operator=(const my_value_reference& other) {
        return operator=(other.operator value_type());
    }
    my_value_reference(value_type& reference) noexcept
        : m_reference{reference} {}
    my_value_reference& operator=(const value_type& value) {
        m_reference = value;
        return *this;
    }
    const my_value_reference& operator=(const value_type& value) const {
        m_reference = value;
        return *this;
    }
    operator value_type() const { return m_reference; }

private:
    value_type& m_reference;
};

template <class T>
class my_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using reference         = my_value_reference<T>; // could just be value_type&
    using const_reference   = reference;             // must be the same

    my_iterator() noexcept                                    = default;
    my_iterator(const my_iterator& other) noexcept            = default;
    my_iterator& operator=(const my_iterator& other) noexcept = default;

    // TODO: implement this
    my_iterator(value_type* ptr) noexcept : m_ptr(ptr) {}

    reference operator*() noexcept {
        // TODO: implement this
        return *m_ptr;
    }

    const_reference operator*() const noexcept {
        // TODO: implement this
        return *m_ptr;
    }

    reference operator[](difference_type index) noexcept {
        return *(*this + index);
    }

    const_reference operator[](difference_type index) const noexcept {
        return *(*this + index);
    }

    my_iterator& operator++() noexcept {
        // TODO: implement this
        ++m_ptr;
        return *this;
    }

    my_iterator operator++(int) noexcept {
        my_iterator temp = *this;
        ++(*this);
        return temp;
    }

    my_iterator& operator--() noexcept {
        // TODO: implement this
        --m_ptr;
        return *this;
    }

    my_iterator operator--(int) noexcept {
        my_iterator temp = *this;
        --(*this);
        return temp;
    }

    my_iterator& operator+=(difference_type n) noexcept {
        // TODO: implement this
        m_ptr += n;
        return *this;
    }

    my_iterator operator+(difference_type n) const noexcept {
        my_iterator result(*this);
        return result += n;
    }

    friend my_iterator operator+(difference_type    n,
                                 const my_iterator& it) noexcept {
        return it + n;
    }

    my_iterator& operator-=(difference_type n) noexcept {
        return *this += (-n);
    }

    my_iterator operator-(difference_type n) const noexcept {
        return *this + (-n);
    }

    friend my_iterator operator-(difference_type    n,
                                 const my_iterator& it) noexcept {
        return it - n;
    }

    difference_type operator-(const my_iterator& other) const noexcept {
        return std::distance(other.m_ptr, m_ptr);
    }

    bool operator==(const my_iterator& other) const noexcept {
        return (other - *this) == 0;
    }

    bool operator!=(const my_iterator& other) const noexcept {
        return !(*this == other);
    }

    bool operator<(const my_iterator& other) const noexcept {
        return 0 < (*this - other);
    }

    bool operator<=(const my_iterator& other) const noexcept {
        return 0 <= (*this - other);
    }

    bool operator>(const my_iterator& other) const noexcept {
        return 0 > (*this - other);
    }

    bool operator>=(const my_iterator& other) const noexcept {
        return 0 >= (*this - other);
    }

private:
    value_type* m_ptr = nullptr;
};

template <class T, size_t N>
class my_container {
public:
    using value_type      = T;
    using iterator        = my_iterator<value_type>;
    using const_iterator  = my_iterator<const value_type>;
    using reference       = decltype(*std::declval<iterator>());
    using const_reference = decltype(*std::declval<const_iterator>());
    using size_type       = size_t;

    my_container() : m_array{} {};
    my_container(const my_container& other) noexcept = default;
    my_container(std::initializer_list<T> init) {
        std::copy(init.begin(), init.end(), begin());
    }

    // Copy constructor that also handles const conversion
    template <class U, class = std::enable_if_t<std::is_same_v<T, U> ||
                                                std::is_convertible_v<U, T>>>
    explicit my_container(my_container<U, N>& other) {
        std::copy(other.begin(), other.end(), begin());
    }

    template <class Iterator>
    my_container(Iterator init_begin, Iterator init_end) {
        std::copy(init_begin, init_end, this->begin());
    }

#ifdef __cpp_lib_ranges
    template <std::ranges::input_range Range>
    my_container(Range&& range) {
        std::ranges::copy(range, this->begin());
    }
#endif

    reference operator[](size_type index) noexcept {
        return *(begin() + index);
    }
    const_reference operator[](size_type index) const noexcept {
        return *(begin() + index);
    }

    iterator       begin() noexcept { return iterator(m_array); }
    const_iterator begin() const noexcept { return const_iterator(m_array); }
    iterator       end() noexcept { return begin() + N; }
    const_iterator end() const noexcept { return begin() + N; }

    value_type*       data() noexcept { return m_array; }
    const value_type* data() const noexcept { m_array; }
    size_type         size() const noexcept { return N; }
    reference         front() noexcept { return *begin(); }
    const_reference   front() const noexcept { return *begin(); }
    reference         back() noexcept { return *(end() - 1); }
    const_reference   back() const noexcept { return *(end() - 1); }

private:
    value_type m_array[N];
};

} // namespace container_boilerplate
