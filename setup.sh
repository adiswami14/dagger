echo 'module load llvm/6.0.1' >> ~/.bashrc
echo 'source setup.sh'
#if [ ! -z $(grep "module load llvm/6.0.1" "$HOME/.bashrc") ]; then echo 'module load llvm/6.0.1' >> $HOME/.bashrc; fi

function cmake_build() {
    mkdir build
    cd build
    cmake3 ..
    git submodule init
    git submodule update
}

cmake_build

function draw_graph() {
    make GraphGenerator
    ./GraphGenerator
    #dot -Tpng graph.dot -o out.png      # Uses built in graphviz drawing algo
    neato -n -Tpng graph.dot -o out_ours.png  # Command that uses our drawing algo
}

function draw_cycle_graph() {
    make cycle
    ./cycle
    #dot -Tpng newcycle.dot -o out.png          # Uses built in graphviz drawing algo
    neato -n -Tpng newcycle.dot -o out_ours.png  # Command that uses our drawing algo
}

# draw_graph
# draw_cycle_graph


function draw_cinder_graph() {
    make CinderGraphGen
    ./CinderGraphGen
    dot -Tpng graph.dot -o out.png
    neato -n -Tpng graph.dot -o out_ours.png 
}
draw_cinder_graph

