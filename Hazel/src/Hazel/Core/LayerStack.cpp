//
// Created by 吴棋凡 on 2023/2/16.
//

#include "hzpch.h"
#include "Hazel/Core/LayerStack.h"

namespace Hazel {

LayerStack::~LayerStack() {
  for (Layer *layer : layers_) {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(Layer *layer) {
  layers_.emplace(layers_.begin() + layer_insert_index_, layer);
  layer_insert_index_++;
}

void LayerStack::PushOverlay(Layer *overlay) { layers_.emplace_back(overlay); }

void LayerStack::PopLayer(Layer *layer) {
  auto iterator = std::find(layers_.begin(), layers_.begin() + layer_insert_index_, layer);
  if (iterator != layers_.begin() + layer_insert_index_) {
    layer->OnDetach();
    layers_.erase(iterator);
    layer_insert_index_--;
  }
}

void LayerStack::PopOverlay(Layer *overlay) {
  auto iterator = std::find(layers_.begin() + layer_insert_index_, layers_.end(), overlay);
  if (iterator != layers_.end()) {
    overlay->OnDetach();
    layers_.erase(iterator);
  }
}

} // namespace Hazel