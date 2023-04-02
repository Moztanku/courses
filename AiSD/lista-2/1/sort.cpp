#include <iostream>
#include <vector>
#include <span>

void insertion_sort(std::span<int> v) noexcept;

void merge_sort(std::span<int> v)  noexcept;

void quick_sort(std::span<int> v)  noexcept;

void double_quick_sort(std::span<int> v)  noexcept;

void hybrid_sort(std::span<int> v)  noexcept;

bool is_sorted(std::vector<int> &v){
    for(int i = 0; i < v.size() - 1; i++)
        if(v[i] > v[i + 1])
            return false;
    return true;
}

static int comparisons = 0;
bool compare(bool a){
    comparisons++;
    return a;
}

static int swaps = 0;
void swap(int &a, int &b){
    swaps++;
    std::swap(a, b);
}

static bool silent = false;
static int N = 0;
static std::vector<int> V;
void print(){
    if(N > 40 || silent)
        return;

    for(auto i : V)
        std::cout << i << " ";
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
    std::cin >> N;

    V = std::vector<int>(N);

    if(argv[2] != nullptr && argv[2] == std::string("silent"))
        silent = true;
    
    for(int i = 0; i < N; i++)
        std::cin >> V[i];

    print();

    if(argv[1] == nullptr || argv[1] == std::string("quick"))
        quick_sort(V);
    else if(argv[1] == std::string("insertion"))
        insertion_sort(V);
    else if(argv[1] == std::string("merge"))
        merge_sort(V);
    else if(argv[1] == std::string("double_quick"))
        double_quick_sort(V);
    else if(argv[1] == std::string("hybrid"))
        hybrid_sort(V);
    else {
        std::cout << "Invalid algorithm!" << std::endl;
        return 1;
    }

    if(!is_sorted(V))
        std::cout << "Not sorted!" << std::endl;

    print();

    if(!silent){
        std::cout << "Swaps: " << swaps << std::endl;
        std::cout << "Comparisons: " << comparisons << std::endl;
    } else {
        std::cout << swaps << std::endl;
        std::cout << comparisons << std::endl;
    }


}

void insertion_sort(std::span<int> v) noexcept{
    const int n = v.size();
    for(int i = 1; i < n; i++){
        int j = i;
        while(j > 0 && compare(v[j - 1] > v[j])){
            swap(v[j - 1], v[j]);
            j--;
        }
    }
}

void merge(const std::span<int> l, const std::span<int> r, std::vector<int>& v){
    int i = 0, j = 0, k = 0;
    while(i < l.size() && j < r.size()){
        if(compare(l[i] < r[j]))
            swap(v[k++], l[i++]);
        else
            swap(v[k++], r[j++]);
    }
    while(i < l.size())
        swap(v[k++], l[i++]);
    while(j < r.size())
        swap(v[k++], r[j++]);
}

void merge_sort(std::span<int> v) noexcept{
    const int n = v.size();
    if(n <= 1)
        return;
    const int m = n / 2;

    merge_sort(v.first(m));
    merge_sort(v.last(n - m));
    
    std::vector<int> tmp(n);
    merge(v.first(m), v.last(n - m), tmp);
    
    for(int i = 0; i < n; i++)
        v[i] = tmp[i];
    print();
}

int partition(std::span<int> v) noexcept{
    int p = v.size() - 1;

    int i = -1;
    for(int j = 0; j < p; j++){
        if(compare(v[j] < v[p])){
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[++i], v[p]);
    return i;
}

void quick_sort(std::span<int> v) noexcept{
    int n = v.size();

    if(n <= 1)
        return;

    int p = partition(v);

    print();

    quick_sort(v.subspan(0, p));
    quick_sort(v.subspan(p + 1, n - 1 - p));
}

std::pair<int,int> double_partition(std::span<int> v) noexcept{
    int n = v.size();
    if(compare(v[0] > v[n-1]))
        swap(v[n-1], v[0]);

    int j = 1;
    int g = n - 2;
    int k = 1;
    int p = v[0];
    int q = v[n-1];

    while(k <= g){
        if(compare(v[k] < p)){
            swap(v[k], v[j]);
            j++;
        }
        else if(compare(v[k] >= q)){
            while(compare(v[g] > q) && k < g)
                g--;
            
            swap(v[k], v[g]);
            g--;

            if(compare(v[k] < p)){
                swap(v[k], v[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;

    swap(v[0], v[j]);
    swap(v[n-1], v[g]);

    return {j,g};
}

void double_quick_sort(std::span<int> v) noexcept{
    const int n = v.size();

    if(n <= 1)
        return;

    auto [p, q] = double_partition(v);

    print();

    double_quick_sort(v.subspan(0, p));
    double_quick_sort(v.subspan(p + 1, q - p - 1));
    double_quick_sort(v.subspan(q + 1, n - 1 - q));
}

void hybrid_sort(std::span<int> v) noexcept{
    // n <= 7 -> insertion sort
    // n > 7 -> double quick sort

    const int n = v.size();

    if(n <= 7){
        insertion_sort(v);
        return;
    }

    auto [p, q] = double_partition(v);

    print();

    hybrid_sort(v.subspan(0, p));
    hybrid_sort(v.subspan(p + 1, q - p - 1));
    hybrid_sort(v.subspan(q + 1, n - 1 - q));
}