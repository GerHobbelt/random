#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "random.hpp"
#include <limits>

using Random = effolkronium::random_static;

#define DOT ::

TEST_CASE( "Range overflow for random integer numbers" ) {
    bool isRangeOverflow = false;

    // From lower to greater
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( )
         && !isRangeOverflow;
         ++i ) {
        const auto randomNumber = Random DOT get( -1, 1 );
        isRangeOverflow = randomNumber < -1 || randomNumber > 1;
    }
    REQUIRE( !isRangeOverflow );

    // From greater to lower
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( );
         ++i ) {
        const auto randomNumber = Random DOT get( 1, -1 );
        isRangeOverflow = randomNumber < -1 || randomNumber > 1;
    }
    REQUIRE( !isRangeOverflow );

    // Range with 0 gap
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( );
         ++i ) {
        const auto randomNumber = Random DOT get( 0, 0 );
        isRangeOverflow = randomNumber != 0;
    }
    REQUIRE( !isRangeOverflow );
}

TEST_CASE( "Type deduction for random integer numbers" ) {
    // short
    static_assert( std::is_same<short,
                   decltype( Random DOT get(
                       short{ 0 },
                       short{ 0 } ) ) > ::value, "" );
    // unsigned short
    static_assert( std::is_same<unsigned short,
                   decltype( Random DOT get(
                       unsigned short{ 0u },
                       unsigned short{ 0u } ) ) > ::value, "" );
    // int
    static_assert( std::is_same<int,
                   decltype( Random DOT get( 0, 0 ) )>::value, "" );
    // unsigned int
    static_assert( std::is_same<unsigned int,
                   decltype( Random DOT get( 0u, 0u ) )>::value, "" );
    // long
    static_assert( std::is_same<long,
                   decltype( Random DOT get( 0l, 0l ) )>::value, "" );
    // unsigned long
    static_assert( std::is_same<unsigned long,
                   decltype( Random DOT get( 0lu, 0lu ) )>::value, "" );
    // long long
    static_assert( std::is_same<long long,
                   decltype( Random DOT get( 0ll, 0ll ) )>::value, "" );
    // unsigned long long
    static_assert( std::is_same<unsigned long long,
                   decltype( Random DOT get( 0ull, 0ull ) )>::value, "" );
}

TEST_CASE( "Random integer numbres is truly random" ) {
    bool isDifferentNumber{ false };

    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( )
         && !isDifferentNumber;
         ++i ) {

        const auto firstRandomNumber = Random DOT get(
            std::numeric_limits<long long>::min( ),
            std::numeric_limits<long long>::max( ) );

        const auto secondRandomNumber = Random DOT get(
            std::numeric_limits<long long>::min( ),
            std::numeric_limits<long long>::max( ) );

        isDifferentNumber = firstRandomNumber != secondRandomNumber;
    }

    // May fail but very rarely
    CHECK( isDifferentNumber );
}

TEST_CASE( "Range overflow for random real numbers" ) {
    bool isRangeOverflow = false;

    // From lower to greater
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( )
         && !isRangeOverflow;
         ++i ) {
        const auto randomNumber = Random DOT get( -1., 1. );
        isRangeOverflow = randomNumber < -1. || randomNumber > 1.;
    }
    REQUIRE( !isRangeOverflow );

    // From greater to lower
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( );
         ++i ) {
        const auto randomNumber = Random DOT get( 1., -1. );
        isRangeOverflow = randomNumber < -1. || randomNumber > 1.;
    }
    REQUIRE( !isRangeOverflow );

    // Range with 0 gap
    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( );
         ++i ) {
        const auto randomNumber = Random DOT get( 0., 0. );
        isRangeOverflow = randomNumber != 0.;
    }
    REQUIRE( !isRangeOverflow );
}

TEST_CASE( "Type deduction for random real numbers" ) {
    // float
    static_assert( std::is_same<float,
                   decltype( Random DOT get(
                       0.f, 0.f ) ) > ::value, "" );
    // double
    static_assert( std::is_same<double,
                   decltype( Random DOT get(
                       0., 0. ) ) > ::value, "" );
    // long double
    static_assert( std::is_same<long double,
                   decltype( Random DOT get( 0.l, 0.l ) )>::value, "" );
}

TEST_CASE( "Random real numbres is truly random" ) {
    bool isDifferentNumber{ false };

    for( std::uint8_t i{ 0u };
         i < std::numeric_limits<std::uint8_t>::max( )
         && !isDifferentNumber;
         ++i ) {

        const auto firstRandomNumber = Random DOT get(
            std::numeric_limits<long double>::min( ),
            std::numeric_limits<long double>::max( ) );

        const auto secondRandomNumber = Random DOT get(
            std::numeric_limits<long double>::min( ),
            std::numeric_limits<long double>::max( ) );

        isDifferentNumber = firstRandomNumber != secondRandomNumber;
    }

    // May fail but very rarely
    CHECK( isDifferentNumber );
}
