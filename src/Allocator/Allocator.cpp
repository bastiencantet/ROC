/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** Allocator
*/
#define VMA_IMPLEMENTATION
#include "Allocator.hpp"

VmaAllocator Rc::Allocator::getAllocator() {
    return m_allocator;
}
