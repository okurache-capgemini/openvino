// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

///////////////////////////////////////////////////////////////////////////////////////////////////

#include "primitive_inst.h"
#include "generic_layer.hpp"
#include "intel_gpu/primitives/activation.hpp"
#include "intel_gpu/primitives/adaptive_pooling.hpp"
#include "intel_gpu/primitives/arg_max_min.hpp"
#include "intel_gpu/primitives/assign.hpp"
#include "intel_gpu/primitives/average_unpooling.hpp"
#include "intel_gpu/primitives/batch_to_space.hpp"
#include "intel_gpu/primitives/binary_convolution.hpp"
#include "intel_gpu/primitives/border.hpp"
#include "intel_gpu/primitives/broadcast.hpp"
#include "intel_gpu/primitives/bucketize.hpp"
#include "intel_gpu/primitives/concatenation.hpp"
#include "intel_gpu/primitives/condition.hpp"
#include "intel_gpu/primitives/convert_color.hpp"
#include "intel_gpu/primitives/convolution.hpp"
#include "intel_gpu/primitives/crop.hpp"
#include "intel_gpu/primitives/ctc_greedy_decoder.hpp"
#include "intel_gpu/primitives/ctc_loss.hpp"
#include "intel_gpu/primitives/cum_sum.hpp"
#include "intel_gpu/primitives/custom_gpu_primitive.hpp"
#include "intel_gpu/primitives/data.hpp"
#include "intel_gpu/primitives/deconvolution.hpp"
#include "intel_gpu/primitives/depth_to_space.hpp"
#include "intel_gpu/primitives/detection_output.hpp"
#include "intel_gpu/primitives/dft.hpp"
#include "intel_gpu/primitives/eltwise.hpp"
#include "intel_gpu/primitives/embedding_bag.hpp"
#include "intel_gpu/primitives/experimental_detectron_detection_output.hpp"
#include "intel_gpu/primitives/experimental_detectron_generate_proposals_single_image.hpp"
#include "intel_gpu/primitives/experimental_detectron_prior_grid_generator.hpp"
#include "intel_gpu/primitives/experimental_detectron_roi_feature_extractor.hpp"
#include "intel_gpu/primitives/experimental_detectron_topk_rois.hpp"
#include "intel_gpu/primitives/extract_image_patches.hpp"
#include "intel_gpu/primitives/eye.hpp"
#include "intel_gpu/primitives/fully_connected.hpp"
#include "intel_gpu/primitives/gather_elements.hpp"
#include "intel_gpu/primitives/gather_nd.hpp"
#include "intel_gpu/primitives/gather_tree.hpp"
#include "intel_gpu/primitives/gather.hpp"
#include "intel_gpu/primitives/gemm.hpp"
#include "intel_gpu/primitives/generate_proposals.hpp"
#include "intel_gpu/primitives/grn.hpp"
#include "intel_gpu/primitives/grn.hpp"
#include "intel_gpu/primitives/input_layout.hpp"
#include "intel_gpu/primitives/loop.hpp"
#include "intel_gpu/primitives/lrn.hpp"
#include "intel_gpu/primitives/lstm_dynamic_input.hpp"
#include "intel_gpu/primitives/lstm_dynamic_timeloop.hpp"
#include "intel_gpu/primitives/lstm_dynamic.hpp"
#include "intel_gpu/primitives/lstm.hpp"
#include "intel_gpu/primitives/multiclass_nms.hpp"
#include "intel_gpu/primitives/mutable_data.hpp"
#include "intel_gpu/primitives/mvn.hpp"
#include "intel_gpu/primitives/non_max_suppression.hpp"
#include "intel_gpu/primitives/non_zero.hpp"
#include "intel_gpu/primitives/normalize.hpp"
#include "intel_gpu/primitives/one_hot.hpp"
#include "intel_gpu/primitives/permute.hpp"
#include "intel_gpu/primitives/pooling.hpp"
#include "intel_gpu/primitives/prior_box.hpp"
#include "intel_gpu/primitives/proposal.hpp"
#include "intel_gpu/primitives/pyramid_roi_align.hpp"
#include "intel_gpu/primitives/quantize.hpp"
#include "intel_gpu/primitives/random_uniform.hpp"
#include "intel_gpu/primitives/range.hpp"
#include "intel_gpu/primitives/read_value.hpp"
#include "intel_gpu/primitives/reduce.hpp"
#include "intel_gpu/primitives/region_yolo.hpp"
#include "intel_gpu/primitives/reorder.hpp"
#include "intel_gpu/primitives/reorg_yolo.hpp"
#include "intel_gpu/primitives/resample.hpp"
#include "intel_gpu/primitives/reshape.hpp"
#include "intel_gpu/primitives/reverse_sequence.hpp"
#include "intel_gpu/primitives/reverse.hpp"
#include "intel_gpu/primitives/roi_align.hpp"
#include "intel_gpu/primitives/roi_pooling.hpp"
#include "intel_gpu/primitives/roll.hpp"
#include "intel_gpu/primitives/scatter_elements_update.hpp"
#include "intel_gpu/primitives/scatter_nd_update.hpp"
#include "intel_gpu/primitives/scatter_update.hpp"
#include "intel_gpu/primitives/select.hpp"
#include "intel_gpu/primitives/shape_of.hpp"
#include "intel_gpu/primitives/shuffle_channels.hpp"
#include "intel_gpu/primitives/slice.hpp"
#include "intel_gpu/primitives/softmax.hpp"
#include "intel_gpu/primitives/space_to_batch.hpp"
#include "intel_gpu/primitives/space_to_depth.hpp"
#include "intel_gpu/primitives/split.hpp"
#include "intel_gpu/primitives/strided_slice.hpp"
#include "intel_gpu/primitives/tile.hpp"

cldnn::primitive_type_id cldnn::get_type_id(std::string type_str) {
    static std::unordered_map<std::string, primitive_type_id> primitive_inst_types = {
        {"activation", cldnn::activation::type_id()},
        {"adaptive_pooling", cldnn::adaptive_pooling::type_id()},
        {"arg_max_min", cldnn::arg_max_min::type_id()},
        {"assign", cldnn::assign::type_id()},
        {"average_unpooling", cldnn::average_unpooling::type_id()},
        {"binary_convolution", cldnn::binary_convolution::type_id()},
        {"border", cldnn::border::type_id()},
        {"broadcast", cldnn::broadcast::type_id()},
        {"bucketize", cldnn::bucketize::type_id()},
        {"batch_to_space", cldnn::batch_to_space::type_id()},
        {"space_to_batch", cldnn::space_to_batch::type_id()},
        {"concatenation", cldnn::concatenation::type_id()},
        {"condition", cldnn::condition::type_id()},
        {"convert_color", cldnn::convert_color::type_id()},
        {"convolution", cldnn::convolution::type_id()},
        {"count_nonzero", cldnn::count_nonzero::type_id()},
        {"crop", cldnn::crop::type_id()},
        {"ctc_greedy_decoder", cldnn::ctc_greedy_decoder::type_id()},
        {"ctc_loss", cldnn::ctc_loss::type_id()},
        {"cum_sum", cldnn::cum_sum::type_id()},
        {"custom_gpu_primitive", cldnn::custom_gpu_primitive::type_id()},
        {"data", cldnn::data::type_id()},
        {"deconvolution", cldnn::deconvolution::type_id()},
        {"deformable_conv", cldnn::deformable_conv::type_id()},
        {"deformable_interp", cldnn::deformable_interp::type_id()},
        {"depth_to_space", cldnn::depth_to_space::type_id()},
        {"detection_output", cldnn::detection_output::type_id()},
        {"dft", cldnn::dft::type_id()},
        {"eltwise", cldnn::eltwise::type_id()},
        {"embedding_bag", cldnn::embedding_bag::type_id()},
        {"experimental_detectron_detection_output", cldnn::experimental_detectron_detection_output::type_id()},
        {"experimental_detectron_generate_proposals_single_image", cldnn::experimental_detectron_generate_proposals_single_image::type_id()},
        {"experimental_detectron_prior_grid_generator", cldnn::experimental_detectron_prior_grid_generator::type_id()},
        {"experimental_detectron_roi_feature_extractor", cldnn::experimental_detectron_roi_feature_extractor::type_id()},
        {"experimental_detectron_topk_rois", cldnn::experimental_detectron_topk_rois::type_id()},
        {"extract_image_patches", cldnn::extract_image_patches::type_id()},
        {"eye", cldnn::eye::type_id()},
        {"fully_connected", cldnn::fully_connected::type_id()},
        {"gather", cldnn::gather::type_id()},
        {"gather_elements", cldnn::gather_elements::type_id()},
        {"gather_nd", cldnn::gather_nd::type_id()},
        {"gather_nonzero", cldnn::gather_nonzero::type_id()},
        {"gather_tree", cldnn::gather_tree::type_id()},
        {"gemm", cldnn::gemm::type_id()},
        {"generate_proposals", cldnn::generate_proposals::type_id()},
        {"generic_layer", cldnn::generic_layer::type_id()},
        {"grn", cldnn::grn::type_id()},
        {"input_layout", cldnn::input_layout::type_id()},
        {"loop", cldnn::loop::type_id()},
        {"lrn", cldnn::lrn::type_id()},
        {"lstm", cldnn::lstm::type_id()},
        {"lstm_dynamic", cldnn::lstm_dynamic::type_id()},
        {"lstm_dynamic_input", cldnn::lstm_dynamic_input::type_id()},
        {"lstm_dynamic_timeloop", cldnn::lstm_dynamic_timeloop::type_id()},
        {"lstm_elt", cldnn::lstm_elt::type_id()},
        {"lstm_gemm", cldnn::lstm_gemm::type_id()},
        {"multiclass_nms", cldnn::multiclass_nms::type_id()},
        {"mutable_data", cldnn::mutable_data::type_id()},
        {"mvn", cldnn::mvn::type_id()},
        {"non_max_suppression", cldnn::non_max_suppression::type_id()},
        {"normalize", cldnn::normalize::type_id()},
        {"one_hot", cldnn::one_hot::type_id()},
        {"permute", cldnn::permute::type_id()},
        {"pooling", cldnn::pooling::type_id()},
        {"prior_box", cldnn::prior_box::type_id()},
        {"proposal", cldnn::proposal::type_id()},
        {"pyramid_roi_align", cldnn::pyramid_roi_align::type_id()},
        {"quantize", cldnn::quantize::type_id()},
        {"random_uniform", cldnn::random_uniform::type_id()},
        {"range", cldnn::range::type_id()},
        {"read_value", cldnn::read_value::type_id()},
        {"reduce", cldnn::reduce::type_id()},
        {"region_yolo", cldnn::region_yolo::type_id()},
        {"reorder", cldnn::reorder::type_id()},
        {"reorg_yolo", cldnn::reorg_yolo::type_id()},
        {"resample", cldnn::resample::type_id()},
        {"reshape", cldnn::reshape::type_id()},
        {"reverse", cldnn::reverse::type_id()},
        {"reverse_sequence", cldnn::reverse_sequence::type_id()},
        {"roi_align", cldnn::roi_align::type_id()},
        {"roi_pooling", cldnn::roi_pooling::type_id()},
        {"roll", cldnn::roll::type_id()},
        {"scatter_elements_update", cldnn::scatter_elements_update::type_id()},
        {"scatter_nd_update", cldnn::scatter_nd_update::type_id()},
        {"scatter_update", cldnn::scatter_update::type_id()},
        {"select", cldnn::select::type_id()},
        {"shape_of", cldnn::shape_of::type_id()},
        {"shuffle_channels", cldnn::shuffle_channels::type_id()},
        {"slice", cldnn::slice::type_id()},
        {"softmax", cldnn::softmax::type_id()},
        {"space_to_depth", cldnn::space_to_depth::type_id()},
        {"split", cldnn::split::type_id()},
        {"strided_slice", cldnn::strided_slice::type_id()},
        {"tile", cldnn::tile::type_id()},
    };

    return primitive_inst_types[type_str];
}