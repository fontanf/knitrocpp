#include <string>
#include <stdexcept>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>

extern "C"
{
#include "knitro.h"
}

namespace knitrocpp
{

using VariableId = KNINT;
using ConstraintId = KNINT;

/**
 * Class for a Knitro context.
 */
class Context
{

public:

    /*
     * Creating and destroying solver objects
     */

    /** Constructor. */
    Context()
    {
        int knitro_return_code = KN_new(&knitro_context_);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::Context - return code: "
                    + std::to_string(knitro_return_code));
        }
        if (knitro_context_ == NULL) {
            throw std::runtime_error(
                    "Failed to find a valid license.");
        }
    }

    /** Destructor. */
    virtual ~Context()
    {
        if (own_context_)
            KN_free(&knitro_context_);
    }

    /*
     * Changing and reading solver parameters
     */

    /** Set an integer valued parameter using its integer identifier. */
    void set_int_param(
            const int param_id,
            const int value)
    {
        int knitro_return_code = KN_set_int_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_int_param - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set a character valued parameter using its integer identifier. */
    void set_char_param(
            const char param_id,
            const char* const value)
    {
        int knitro_return_code = KN_set_char_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_char_param - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set a double valued parameter using its integer identifier. */
    void set_double_param(
            const double param_id,
            const double value)
    {
        int knitro_return_code = KN_set_double_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_double_param - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Basic problem construction
     */

    /** Add a variable to the problem. */
    VariableId add_var()
    {
        VariableId variable_id = -1;
        int knitro_return_code = KN_add_var(
                knitro_context_,
                &variable_id);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_var - return code: "
                    + std::to_string(knitro_return_code));
        }
        return variable_id;
    }

    /** Add an empty constraint to the problem. */
    ConstraintId add_con()
    {
        ConstraintId constraint_id = -1;
        int knitro_return_code = KN_add_con(
                knitro_context_,
                &constraint_id);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_con - return code: "
                    + std::to_string(knitro_return_code));
        }
        return constraint_id;
    }

    /** Set the lower bound of a variable. */
    void set_var_lobnd(
            VariableId variable_id,
            double lower_bound)
    {
        int knitro_return_code = KN_set_var_lobnd(
                knitro_context_,
                variable_id,
                lower_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_var_lobnd - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set the upper bound of a variable. */
    void set_var_upbnd(
            VariableId variable_id,
            double upper_bound)
    {
        int knitro_return_code = KN_set_var_upbnd(
                knitro_context_,
                variable_id,
                upper_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_var_upbnd - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Get the lower bound of a variable. */
    double get_var_lobnd(
            VariableId variable_id) const
    {
        double lower_bound = 0.0;
        int knitro_return_code = KN_get_var_lobnd(
                knitro_context_,
                variable_id,
                &lower_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_var_lobnd - return code: "
                    + std::to_string(knitro_return_code));
        }
        return lower_bound;
    }

    /** Get the upper bound of a variable. */
    double get_var_upbnd(
            VariableId variable_id) const
    {
        double upper_bound = 0.0;
        int knitro_return_code = KN_get_var_upbnd(
                knitro_context_,
                variable_id,
                &upper_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_var_upbnd - return code: "
                    + std::to_string(knitro_return_code));
        }
        return upper_bound;
    }

    /** Set the type of a variable. */
    void set_var_type(
            VariableId variable_id,
            int variable_type)
    {
        int knitro_return_code = KN_set_var_type(
                knitro_context_,
                variable_id,
                variable_type);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_var_type - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Get the type of a variable. */
    int get_var_type(
            VariableId variable_id) const
    {
        int variable_type = -1;
        int knitro_return_code = KN_get_var_type(
                knitro_context_,
                variable_id,
                &variable_type);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_var_type - return code: "
                    + std::to_string(knitro_return_code));
        }
        return variable_type;
    }

    /** Set the lower bound of a constraint. */
    void set_con_lobnd(
            ConstraintId constraint_id,
            double lower_bound)
    {
        int knitro_return_code = KN_set_con_lobnd(
                knitro_context_,
                constraint_id,
                lower_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_con_lobnd - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set the upper bound of a constraint. */
    void set_con_upbnd(
            ConstraintId constraint_id,
            double upper_bound)
    {
        int knitro_return_code = KN_set_con_upbnd(
                knitro_context_,
                constraint_id,
                upper_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_con_upbnd - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Get the lower bound of a constraint. */
    double get_con_lobnd(
            ConstraintId constraint_id) const
    {
        double lower_bound = 0.0;
        int knitro_return_code = KN_get_con_lobnd(
                knitro_context_,
                constraint_id,
                &lower_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_con_lobnd - return code: "
                    + std::to_string(knitro_return_code));
        }
        return lower_bound;
    }

    /** Get the upper bound of a constraint. */
    double get_con_upbnd(
            ConstraintId constraint_id) const
    {
        double upper_bound = 0.0;
        int knitro_return_code = KN_get_con_upbnd(
                knitro_context_,
                constraint_id,
                &upper_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_con_upbnd - return code: "
                    + std::to_string(knitro_return_code));
        }
        return upper_bound;
    }

    /** Set the objective goal (KN_OBJGOAL_MINIMIZE or KN_OBJGOAL_MAXIMIZE). */
    void set_obj_goal(
            int objective_goal)
    {
        int knitro_return_code = KN_set_obj_goal(
                knitro_context_,
                objective_goal);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_obj_goal - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set the intial value of a primal variable. */
    void set_var_primal_init_value(
            VariableId variable_id,
            double value)
    {
        int knitro_return_code = KN_set_var_primal_init_value(
                knitro_context_,
                variable_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_var_primal_init_value - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set the intial value of a dual variable. */
    void set_var_dual_init_value(
            VariableId variable_id,
            double value)
    {
        int knitro_return_code = KN_set_var_dual_init_value(
                knitro_context_,
                variable_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_var_dual_init_value - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Set the intial value of a dual constraint. */
    void set_con_dual_init_value(
            ConstraintId constraint_id,
            double value)
    {
        int knitro_return_code = KN_set_con_dual_init_value(
                knitro_context_,
                constraint_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_con_dual_init_value - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Adding/removing/changing constant structure
     */

    /*
     * Adding/removing/changing linear structure
     */

    /** Add linear structure to the objective function. */
    void add_obj_linear_term(
            VariableId variable_id,
            const double coefficient)
    {
        int knitro_return_code = KN_add_obj_linear_term (
                knitro_context_,
                variable_id,
                coefficient);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_obj_linear_term - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Add linear structure to the constraint functions. */
    void add_con_linear_term(
            ConstraintId constraint_id,
            VariableId variable_id,
            const double coefficient)
    {
        int knitro_return_code = KN_add_con_linear_term(
                knitro_context_,
                constraint_id,
                variable_id,
                coefficient);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_con_linear_term - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Add quadratic structure to the objective. */
    void add_obj_quadratic_term(
            VariableId variable_id_1,
            VariableId variable_id_2,
            const double coefficient)
    {
        int knitro_return_code = KN_add_obj_quadratic_term(
                knitro_context_,
                variable_id_1,
                variable_id_2,
                coefficient);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_obj_quadratic_term - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /** Add quadratic structure to the constraint functions. */
    void add_con_quadratic_term(
            ConstraintId constraint_id,
            VariableId variable_id_1,
            VariableId variable_id_2,
            const double coefficient)
    {
        int knitro_return_code = KN_add_con_quadratic_term(
                knitro_context_,
                constraint_id,
                variable_id_1,
                variable_id_2,
                coefficient);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_con_quadratic_term - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Adding quadratic structure
     */

    /*
     * Adding conic structure
     */

    /*
     * Adding complementarity constraints
     */

    /*
     * Adding evaluation callbacks
     */

    using EvalCallback = std::function<int(
            const Context&,
            CB_context_ptr,
            KN_eval_request_ptr const,
            KN_eval_result_ptr const)>;

    struct EvalCallbackStruct
    {
        EvalCallback eval_callback;
        EvalCallback gradient;
        EvalCallback hessian;
    };

    static int eval_callback(
            KN_context* kc,
            CB_context* callback_context,
            KN_eval_request_ptr const eval_request,
            KN_eval_result_ptr const eval_result,
            void* const user_params)
    {
        EvalCallbackStruct* eval_callback_struct = (EvalCallbackStruct*)user_params;
        Context knitro_context(kc);
        return eval_callback_struct->eval_callback(
                knitro_context,
                callback_context,
                eval_request,
                eval_result);
    }

    CB_context* add_eval_callback(
            bool evaluate_objective,
            const std::vector<ConstraintId>& constraint_ids,
            EvalCallback eval_callback_function)
    {
        EvalCallbackStruct eval_callback_struct;
        eval_callback_struct.eval_callback = eval_callback_function;
        eval_callbacks_.push_back(std::unique_ptr<EvalCallbackStruct>(
                    new EvalCallbackStruct(eval_callback_struct)));
        CB_context* callback_context;
        int knitro_return_code = KN_add_eval_callback(
                knitro_context_,
                evaluate_objective,
                constraint_ids.size(),
                constraint_ids.data(),
                eval_callback,
                &callback_context);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_eval_callback - return code: "
                    + std::to_string(knitro_return_code));
        }
        knitro_return_code = KN_set_cb_user_params(
                knitro_context_,
                callback_context,
                eval_callbacks_.back().get());
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::add_eval_callback - return code: "
                    + std::to_string(knitro_return_code));
        }
        cb2eval_[callback_context] = eval_callbacks_.back().get();
        return callback_context;
    }

    static int gradient_callback(
            KN_context* kc,
            CB_context* callback_context,
            KN_eval_request_ptr const eval_request,
            KN_eval_result_ptr const eval_result,
            void* const user_params)
    {
        EvalCallbackStruct* eval_callback_struct = (EvalCallbackStruct*)user_params;
        Context knitro_context(kc);
        return eval_callback_struct->gradient(
                knitro_context,
                callback_context,
                eval_request,
                eval_result);
    }

    void set_cb_grad(
            CB_context* callback_context,
            std::vector<VariableId>* objgrad_variable_ids,
            std::vector<ConstraintId>* jacobian_constraint_ids,
            std::vector<VariableId>* jacobian_variable_ids,
            EvalCallback gradient_callback_function)
    {
        EvalCallbackStruct* eval_callback_struct = cb2eval_[callback_context];
        eval_callback_struct->gradient = gradient_callback_function;
        int knitro_return_code = KN_set_cb_grad(
                knitro_context_,
                callback_context,
                (objgrad_variable_ids == nullptr)? KN_DENSE: objgrad_variable_ids->size(),
                (objgrad_variable_ids == nullptr)? nullptr: objgrad_variable_ids->data(),
                (jacobian_constraint_ids == nullptr)? KN_DENSE: jacobian_constraint_ids->size(),
                (jacobian_constraint_ids == nullptr)? nullptr: jacobian_constraint_ids->data(),
                (jacobian_variable_ids == nullptr)? nullptr: jacobian_variable_ids->data(),
                gradient_callback);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_cb_grad - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    static int hessian_callback(
            KN_context* kc,
            CB_context* callback_context,
            KN_eval_request_ptr const eval_request,
            KN_eval_result_ptr const eval_result,
            void* const user_params)
    {
        EvalCallbackStruct* eval_callback_struct = (EvalCallbackStruct*)user_params;
        Context knitro_context(kc);
        return eval_callback_struct->hessian(
                knitro_context,
                callback_context,
                eval_request,
                eval_result);
    }

    void set_cb_hess(
            CB_context* callback_context,
            std::vector<VariableId>* variable_ids_1,
            std::vector<VariableId>* variable_ids_2,
            EvalCallback hessian_callback_function)
    {
        EvalCallbackStruct* eval_callback_struct = cb2eval_[callback_context];
        eval_callback_struct->hessian = hessian_callback_function;
        int knitro_return_code = KN_set_cb_hess(
                knitro_context_,
                callback_context,
                (variable_ids_1 == nullptr)? KN_DENSE_ROWMAJOR: variable_ids_1->size(),
                (variable_ids_1 == nullptr)? nullptr: variable_ids_1->data(),
                (variable_ids_1 == nullptr)? nullptr: variable_ids_2->data(),
                hessian_callback);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_cb_hess - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Other user callbacks
     */

    using UserCallback = std::function<int(const Context&, const double* const, const double* const)>;

    static int mip_node_callback(
            KN_context* kc,
            const double* const x,
            const double* const lambda,
            void* const user_params)
    {
        Context* knitro_context_orig = (Context*)user_params;
        Context knitro_context(kc);
        return knitro_context_orig->mip_node_callback_(knitro_context, x, lambda);
    }

    /** Set the MIP node callback. */
    void set_mip_node_callback(
            UserCallback mip_node_callback_function)
    {
        mip_node_callback_ = mip_node_callback_function;
        int knitro_return_code = KN_set_mip_node_callback(
                knitro_context_,
                mip_node_callback,
                (void* const)this);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_mip_node_callback - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Other algorithmic/modeling features
     */

    /** Set the value of a primal variable from a primal solution for a MIP. */
    void set_mip_var_primal_init_value(
            VariableId variable_id,
            double value)
    {
        int knitro_return_code = KN_set_mip_var_primal_init_value(
                knitro_context_,
                variable_id,
                value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::set_mip_var_primal_init_value - return code: "
                    + std::to_string(knitro_return_code));
        }
    }

    /*
     * Solving
     */

    /* Call Knitro to solve the problem. */
    int solve()
    {
        return KN_solve(knitro_context_);
    }

    /*
     * Reading model/solution properties
     */

    /** Get the number of variables in the model. */
    VariableId get_number_vars() const
    {
        VariableId number_of_variables = -1;
        int knitro_return_code = KN_get_number_vars(
                knitro_context_,
                &number_of_variables);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_number_vars - return code: "
                    + std::to_string(knitro_return_code));
        }
        return number_of_variables;
    }

    /** Get the number of constraints in the model. */
    ConstraintId get_number_cons() const
    {
        ConstraintId number_of_constraints = -1;
        int knitro_return_code = KN_get_number_cons(
                knitro_context_,
                &number_of_constraints);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_number_cons - return code: "
                    + std::to_string(knitro_return_code));
        }
        return number_of_constraints;
    }

    /** Get the value of the objective. */
    double get_obj_value() const
    {
        double objective = 0.0;
        int knitro_return_code = KN_get_obj_value(
                knitro_context_,
                &objective);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_obj_value - return code: "
                    + std::to_string(knitro_return_code));
        }
        return objective;
    }

    /** Get the value of a primal variable. */
    double get_var_primal_value(
            VariableId variable_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_var_primal_value (
                knitro_context_,
                variable_id,
                &value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_var_primal_value - return code: "
                    + std::to_string(knitro_return_code));
        }
        return value;
    }

    /** Get the value of a dual variable. */
    double get_var_dual_value(
            VariableId variable_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_var_dual_value (
                knitro_context_,
                variable_id,
                &value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_var_dual_value - return code: "
                    + std::to_string(knitro_return_code));
        }
        return value;
    }

    /** Get the dual value of a constraint. */
    double get_con_dual_value(
            ConstraintId constraint_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_con_dual_value (
                knitro_context_,
                constraint_id,
                &value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_con_dual_value - return code: "
                    + std::to_string(knitro_return_code));
        }
        return value;
    }

    /** Get the value of a constraint. */
    double get_con_value(
            ConstraintId constraint_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_con_value (
                knitro_context_,
                constraint_id,
                &value);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_con_value - return code: "
                    + std::to_string(knitro_return_code));
        }
        return value;
    }

    /** Get the absolute feasibility error at the solution. */
    double get_abs_feas_error()
    {
        double abs_feas_error = -1;
        int knitro_return_code = KN_get_abs_feas_error(
                knitro_context_,
                &abs_feas_error);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_abs_feas_error - return code: "
                    + std::to_string(knitro_return_code));
        }
        return abs_feas_error;
    }

    /** Get the relative feasibility error at the solution. */
    double get_rel_feas_error()
    {
        double rel_feas_error = -1;
        int knitro_return_code = KN_get_rel_feas_error(
                knitro_context_,
                &rel_feas_error);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_rel_feas_error - return code: "
                    + std::to_string(knitro_return_code));
        }
        return rel_feas_error;
    }

    /** Get the absolute optimality error at the solution. */
    double get_abs_opt_error()
    {
        double abs_opt_error = -1;
        int knitro_return_code = KN_get_abs_opt_error(
                knitro_context_,
                &abs_opt_error);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_abs_opt_error - return code: "
                    + std::to_string(knitro_return_code));
        }
        return abs_opt_error;
    }

    /** Get the relative optimality error at the solution. */
    double get_rel_opt_error()
    {
        double rel_opt_error = -1;
        int knitro_return_code = KN_get_rel_opt_error(
                knitro_context_,
                &rel_opt_error);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_rel_opt_error - return code: "
                    + std::to_string(knitro_return_code));
        }
        return rel_opt_error;
    }

    /** Get the objective value of the MIP incumbent solution. */
    bool has_mip_incumbent() const
    {
        double incumbent_objective;
        int knitro_return_code = KN_get_mip_incumbent_obj(
                knitro_context_,
                &incumbent_objective);
        if (knitro_return_code < 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_mip_incumbent_obj - return code: "
                    + std::to_string(knitro_return_code));
        }
        return (knitro_return_code == 0);
    }

    /** Get the objective value of the MIP incumbent solution. */
    double get_mip_incumbent_obj() const
    {
        double incumbent_objective;
        int knitro_return_code = KN_get_mip_incumbent_obj(
                knitro_context_,
                &incumbent_objective);
        if (knitro_return_code < 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_mip_incumbent_obj - return code: "
                    + std::to_string(knitro_return_code));
        }
        return incumbent_objective;
    }

    /** Get the value of the current MIP relaxation bound. */
    double get_mip_relaxation_bnd() const
    {
        double relaxation_bound = 0.0;
        int knitro_return_code = KN_get_mip_relaxation_bnd(
                knitro_context_,
                &relaxation_bound);
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_mip_relaxation_bnd - return code: "
                    + std::to_string(knitro_return_code));
        }
        return relaxation_bound;
    }

    /** Get the MIP incumbent solution. */
    std::vector<double> get_mip_incumbent_x() const
    {
        std::vector<double> mip_incumbent_x(get_number_vars(), 0.0);
        int knitro_return_code = KN_get_mip_incumbent_x(
                knitro_context_,
                mip_incumbent_x.data());
        if (knitro_return_code != 0) {
            throw std::runtime_error(
                    "knitrocpp::Context::get_mip_incumbent_x - return code: "
                    + std::to_string(knitro_return_code));
        }
        return mip_incumbent_x;
    }

private:

    /*
     * Private attributes
     */

    /** Knitro context. */
    KN_context* knitro_context_ = nullptr;

    /** Boolean indicating if this context owns its C context. */
    bool own_context_ = true;

    /** Evaluation callbacks. */
    std::vector<std::unique_ptr<EvalCallbackStruct>> eval_callbacks_;

    std::unordered_map<CB_context*, EvalCallbackStruct*> cb2eval_;

    /** MIP node callback. */
    UserCallback mip_node_callback_;

    /*
     * Private methods
     */

    /** Constructor from an already existing C context. */
    Context(KN_context* knitro_context):
        knitro_context_(knitro_context),
        own_context_(false) { }

};

}
