#ifndef XY_INTERPRETER_H
#define XY_INTERPRETER_H

#include <variant>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

namespace XY {

    // ==========================================
    // 1. THE DATA TYPE (Runtime Script Object)
    // ==========================================
    class Node {
    public:
        // Nested Error class for runtime interpreter panics
        class Error : public std::runtime_error {
        public:
            explicit Error(const std::string& message) 
                : std::runtime_error("XY::Node Runtime Error - " + message) {}
        };

        // Holds the script value (C++17 variant)
        std::variant<int, std::string> value;

        // Connections to other script nodes (e.g., fields inside a user object)
        std::vector<Node*> references;

        // Lightweight tracking marker for the Collector (~1 byte overhead)
        bool isMarked = false;

        explicit Node(std::variant<int, std::string> val) : value(val) {}
        ~Node() = default; 
    };

    // ==========================================
    // 2. THE SUBSYSTEM (Garbage Collector)
    // ==========================================
    class Collector {
    private:
        // Master Heap: Owns the real allocations of all active or dead nodes
        std::vector<std::unique_ptr<Node>> heap;

    public:
        Collector() = default;
        ~Collector() = default;

        // Factory pattern: The collector spawns nodes and logs their allocation
        Node* allocate(std::variant<int, std::string> initialValue) {
            auto new_node = std::make_unique<Node>(initialValue);
            Node* raw_pointer = new_node.get();
            heap.push_back(std::move(new_node));
            return raw_pointer;
        }

        // The central loop that fires when functions exit or memory fills up
        void sweep(const std::vector<Node*>& root_set) {
            // Step 1: Mark phase (traverse starting from active root variables)
            for (Node* root : root_set) {
                mark(root);
            }

            // Step 2: Sweep phase (delete anything left unmarked)
            auto it = heap.begin();
            while (it != heap.end()) {
                if (!(*it)->isMarked) {
                    it = heap.erase(it); // Automatically calls ~Node() and frees RAM
                } else {
                    (*it)->isMarked = false; // Reset the flag for the next GC pass
                    ++it;
                }
            }
        }

    private:
        // Helper method to recursively mark nested structures without crashing
        void mark(Node* node) {
            if (!node || node->isMarked) return;
            
            node->isMarked = true;
            
            // Recurse through any user variables linked inside this object
            for (Node* edge : node->references) {
                mark(edge);
            }
        }
    };

} // namespace XY

#endif // XY_INTERPRETER_H

