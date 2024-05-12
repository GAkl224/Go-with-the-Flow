#include <iostream>
#include <map>

using namespace std;

class HeatFlow {
private:
    float initial_temperature;
    int num_sections;
    float K;
    map<int, float> sources_and_sinks;
    map<int, float> temperatures;

public:
    HeatFlow(float initial_temp, int sections, float k, map<int, float> sources) :
    
            initial_temperature(initial_temp), num_sections(sections), K(k), sources_and_sinks(sources) {

        for (int i = 0; i < num_sections; ++i) {

            temperatures[i] = initial_temp;
        }
        for (const auto& kv : sources_and_sinks) {

            temperatures[kv.first] = kv.second;
        }
    }

    void tick() {
        map<int, float> new_temperatures;

        for (int i = 0; i < num_sections; ++i) {

            if (sources_and_sinks.find(i) != sources_and_sinks.end()) {
                new_temperatures[i] = sources_and_sinks[i];

            } else {
                float prev_temp = temperatures[i];
                float left_temp = (i == 0) ? initial_temperature : temperatures[i - 1];
                float right_temp = (i == num_sections - 1) ? initial_temperature : temperatures[i + 1];
                float next_temp = prev_temp + K * (left_temp - 2 * prev_temp + right_temp);
                new_temperatures[i] = next_temp;
            }
        }
        temperatures = new_temperatures;
    }

    void pretty_print() {

        cout << "+";

        for (int i = 0; i < num_sections; ++i) {
            cout << "------+";
        }
        cout << endl << "|";
        for (int i = 0; i < num_sections; ++i) {
            printf(" %4.1f |", temperatures[i]);
        }
        cout << endl << "+";
        for (int i = 0; i < num_sections; ++i) {
            cout << "------+";
        }
        cout << endl;
    }
};

int main() {
    map<int, float> sources_and_sinks;

    sources_and_sinks[0] = 100.0;

    float initial_temperature = 10.0;

    int number_of_sections = 5;
    
    float K = 0.1;

    HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
    h.pretty_print();

    h.tick();
    h.pretty_print();

    h.tick();
    h.pretty_print();

    return 0;
}
