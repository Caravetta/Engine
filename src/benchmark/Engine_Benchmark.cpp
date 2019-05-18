#include <benchmark/benchmark.h>
#include "page_allocator.h"

static void PageAllocatorInit(benchmark::State& state)
{
     for ( auto _ : state ) {
          Engine::Rc_t rc = Engine::init_page_allocator(16000, 100);
          if ( rc != Engine::SUCCESS ) {
               LOG("Failed to init page allocator rc=%d", rc);
          }
          state.PauseTiming();
          Engine::destroy_page_allocator();
          state.ResumeTiming();
     }
}

BENCHMARK(PageAllocatorInit)->Complexity();

class PageAllocator : public ::benchmark::Fixture {
public:
     void SetUp(const ::benchmark::State& state) {
          Engine::Rc_t rc = Engine::init_page_allocator(16000, 100);
          if ( rc != Engine::SUCCESS ) {
               LOG("Failed to init page allocator rc=%d", rc);
          }
     }

     void TearDown(const ::benchmark::State& state) {
          Engine::destroy_page_allocator();
     }

};

BENCHMARK_DEFINE_F(PageAllocator, get_page)(benchmark::State& state)
{
     for ( auto _ : state ) {
          void* page = Engine::allocate_page();

          state.PauseTiming();
          Engine::free_page(page);
          state.ResumeTiming();
     }
}

BENCHMARK_REGISTER_F(PageAllocator, get_page)->Complexity();

static void get_page_malloc(benchmark::State& state)
{
     for ( auto _ : state ) {
          void* page;

          //benchmark::DoNotOptimize(page = malloc(16000));
          page = malloc(16000);

          state.PauseTiming();
          free(page);
          state.ResumeTiming();
     }
}

BENCHMARK(get_page_malloc)->Complexity();

BENCHMARK_DEFINE_F(PageAllocator, free_page)(benchmark::State& state)
{
     for ( auto _ : state ) {
          state.PauseTiming();
          void* page = Engine::allocate_page();
          state.ResumeTiming();

          Engine::free_page(page);
     }
}

BENCHMARK_REGISTER_F(PageAllocator, free_page)->Complexity();

BENCHMARK_MAIN();

