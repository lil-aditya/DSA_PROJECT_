
#include <iostream>
#include <string>
#include "number_theory.hpp"
#include "rsa_signature.hpp"
#include "hashing.hpp"
#include "hashmap.hpp"
#include "priority_engine.hpp"
#include "graph_routing.hpp"

int main() {
    std::cout << "\n--- ADIPE DEMO (Toy) ---\n";

    // 1. Generate RSA keys (toy)
    RSAKeys keys = generateRSAKeys();
    std::cout << "RSA n: " << keys.n << " e: " << keys.e << " d: " << keys.d << "\\n";

    // 2. Hash & Sign
    std::string data = \"CriticalDataPacket-Example\";
    uint64_t h = simpleHash(data);
    uint64_t sig = signData(h, keys);
    uint64_t verify = verifySignature(sig, keys);
    std::cout << \"Data: \" << data << \"\\nHash: \" << h << \"\\nSignature: \" << sig << \"\\nVerified Hash: \" << verify << \"\\n\";
    std::cout << \"Signature verification: \" << (verify == h ? \"SUCCESS\" : \"FAIL\") << \"\\n\\n\";

    // 3. Metadata store demo
    MetadataMap meta;
    meta.insert(\"UserA_pub\", \"pubkey_userA_example\");
    std::cout << \"Lookup UserA_pub: \" << meta.get(\"UserA_pub\") << \"\\n\\n\";

    // 4. Prioritizer demo
    PriorityEngine engine;
    engine.push(DataPacket{\"pkt1\", 10});
    engine.push(DataPacket{\"pkt2\", 5});
    engine.push(DataPacket{\"pkt3\", 20});
    std::cout << \"Processing Packets by urgency:\\n\";
    while (!engine.empty()) {
        auto p = engine.pop();
        if (p) std::cout << \" - \" << p->id << \" (urgency=\" << p->urgency << \")\\n\";
    }
    std::cout << \"\\n\";

    // 5. Graph routing demo
    Graph g(6);
    g.addEdge(0,1); g.addEdge(0,2); g.addEdge(1,3); g.addEdge(2,4); g.addEdge(4,5);
    auto order = g.BFS(0);
    std::cout << \"BFS order from node 0: \";
    for (int v: order) std::cout << v << \" \";
    std::cout << \"\\n\\n--- END ---\\n\";
    return 0;
}
