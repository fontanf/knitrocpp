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
 * Class for handling Knitro exceptions.
 */
class KnitroException: public std::exception
{

public:

    KnitroException(
            const std::string& function_name,
            int return_code)
    {
        message_
            = "KnitroCpp error: return code for C function '"
            + function_name + "' is "
            + std::to_string(return_code) + ".";
    }

    const char * what() const noexcept override
    {
        return message_.c_str();
    }

private:

    std::string message_;

};

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
        if (knitro_return_code != 0)
            throw KnitroException("KN_new", knitro_return_code);
        if (knitro_context_ == NULL)
            throw std::runtime_error("Failed to find a valid license.");
    }

    /** Destructor. */
    ~Context()
    {
        if (own_context_)
            KN_free(&knitro_context_);
    }

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    /*
     * Changing and reading solver parameters
     */

    /** Reset all parameters to their default values. */
    void reset_params_to_defaults()
    {
        int knitro_return_code = KN_reset_params_to_defaults(knitro_context_);
        if (knitro_return_code != 0)
            throw KnitroException("KN_reset_params_to_defaults", knitro_return_code);
    }

    /** Load all parameters from a file. */
    void load_param_file(const std::string& filename)
    {
        int knitro_return_code = KN_load_param_file(
                knitro_context_,
                filename.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_load_param_file", knitro_return_code);
    }

    /** Save all current parameter values to a file. */
    void save_param_file(const std::string& filename)
    {
        int knitro_return_code = KN_save_param_file(
                knitro_context_,
                filename.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_save_param_file", knitro_return_code);
    }

    /** Set an integer valued parameter using its integer identifier. */
    void set_int_param(
            const int param_id,
            const int value)
    {
        int knitro_return_code = KN_set_int_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_int_param", knitro_return_code);
    }

    /** Set a character valued parameter using its integer identifier. */
    void set_char_param(
            const int param_id,
            const char* const value)
    {
        int knitro_return_code = KN_set_char_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_char_param", knitro_return_code);
    }

    /** Set a double valued parameter using its integer identifier. */
    void set_double_param(
            const int param_id,
            const double value)
    {
        int knitro_return_code = KN_set_double_param(
                knitro_context_,
                param_id,
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_double_param", knitro_return_code);
    }

    /** Set an integer valued parameter using its string name. */
    void set_int_param_by_name(
            const std::string& name,
            const int value)
    {
        int knitro_return_code = KN_set_int_param_by_name(
                knitro_context_,
                name.c_str(),
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_int_param_by_name", knitro_return_code);
    }

    /** Set a character valued parameter using its string name. */
    void set_char_param_by_name(
            const std::string& name,
            const std::string& value)
    {
        int knitro_return_code = KN_set_char_param_by_name(
                knitro_context_,
                name.c_str(),
                value.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_char_param_by_name", knitro_return_code);
    }

    /** Set a double valued parameter using its string name. */
    void set_double_param_by_name(
            const std::string& name,
            const double value)
    {
        int knitro_return_code = KN_set_double_param_by_name(
                knitro_context_,
                name.c_str(),
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_double_param_by_name", knitro_return_code);
    }

    /** Get an integer valued parameter using its integer identifier. */
    int get_int_param(const int param_id) const
    {
        int value = 0;
        int knitro_return_code = KN_get_int_param(
                knitro_context_,
                param_id,
                &value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_int_param", knitro_return_code);
        return value;
    }

    /** Get a double valued parameter using its integer identifier. */
    double get_double_param(const int param_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_double_param(
                knitro_context_,
                param_id,
                &value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_double_param", knitro_return_code);
        return value;
    }

    /** Get an integer valued parameter using its string name. */
    int get_int_param_by_name(const std::string& name) const
    {
        int value = 0;
        int knitro_return_code = KN_get_int_param_by_name(
                knitro_context_,
                name.c_str(),
                &value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_int_param_by_name", knitro_return_code);
        return value;
    }

    /** Get a double valued parameter using its string name. */
    double get_double_param_by_name(const std::string& name) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_double_param_by_name(
                knitro_context_,
                name.c_str(),
                &value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_double_param_by_name", knitro_return_code);
        return value;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_var", knitro_return_code);
        return variable_id;
    }

    /** Add number_of_variables variables to the problem, returning their ids. */
    std::vector<VariableId> add_vars(VariableId number_of_variables)
    {
        std::vector<VariableId> variable_ids(number_of_variables, -1);
        int knitro_return_code = KN_add_vars(
                knitro_context_,
                number_of_variables,
                variable_ids.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_vars", knitro_return_code);
        return variable_ids;
    }

    /** Add an empty constraint to the problem. */
    ConstraintId add_con()
    {
        ConstraintId constraint_id = -1;
        int knitro_return_code = KN_add_con(
                knitro_context_,
                &constraint_id);
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con", knitro_return_code);
        return constraint_id;
    }

    /** Add number_of_constraints constraints to the problem, returning their ids. */
    std::vector<ConstraintId> add_cons(ConstraintId number_of_constraints)
    {
        std::vector<ConstraintId> constraint_ids(number_of_constraints, -1);
        int knitro_return_code = KN_add_cons(
                knitro_context_,
                number_of_constraints,
                constraint_ids.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_cons", knitro_return_code);
        return constraint_ids;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_lobnd", knitro_return_code);
    }

    /** Set the lower bounds of a subset of variables. */
    void set_var_lobnds(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& lower_bounds)
    {
        int knitro_return_code = KN_set_var_lobnds(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                lower_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_lobnds", knitro_return_code);
    }

    /** Set the lower bounds of all variables. */
    void set_var_lobnds(
            const std::vector<double>& lower_bounds)
    {
        int knitro_return_code = KN_set_var_lobnds_all(
                knitro_context_,
                lower_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_lobnds_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_upbnd", knitro_return_code);
    }

    /** Set the upper bounds of a subset of variables. */
    void set_var_upbnds(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& upper_bounds)
    {
        int knitro_return_code = KN_set_var_upbnds(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                upper_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_upbnds", knitro_return_code);
    }

    /** Set the upper bounds of all variables. */
    void set_var_upbnds(
            const std::vector<double>& upper_bounds)
    {
        int knitro_return_code = KN_set_var_upbnds_all(
                knitro_context_,
                upper_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_upbnds_all", knitro_return_code);
    }

    /** Set a fixed bound on a variable (lower == upper). */
    void set_var_fxbnd(
            VariableId variable_id,
            double fixed_bound)
    {
        int knitro_return_code = KN_set_var_fxbnd(
                knitro_context_,
                variable_id,
                fixed_bound);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_fxbnd", knitro_return_code);
    }

    /** Set fixed bounds on a subset of variables. */
    void set_var_fxbnds(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& fixed_bounds)
    {
        int knitro_return_code = KN_set_var_fxbnds(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                fixed_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_fxbnds", knitro_return_code);
    }

    /** Set fixed bounds on all variables. */
    void set_var_fxbnds(
            const std::vector<double>& fixed_bounds)
    {
        int knitro_return_code = KN_set_var_fxbnds_all(
                knitro_context_,
                fixed_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_fxbnds_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_lobnd", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_upbnd", knitro_return_code);
        return upper_bound;
    }

    /** Get the fixed bound of a variable. */
    double get_var_fxbnd(
            VariableId variable_id) const
    {
        double fixed_bound = 0.0;
        int knitro_return_code = KN_get_var_fxbnd(
                knitro_context_,
                variable_id,
                &fixed_bound);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_fxbnd", knitro_return_code);
        return fixed_bound;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_type", knitro_return_code);
    }

    /** Set the types of a subset of variables. */
    void set_var_types(
            const std::vector<VariableId>& variable_ids,
            const std::vector<int>& variable_types)
    {
        int knitro_return_code = KN_set_var_types(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                variable_types.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_types", knitro_return_code);
    }

    /** Set the types of all variables. */
    void set_var_types(
            const std::vector<int>& variable_types)
    {
        int knitro_return_code = KN_set_var_types_all(
                knitro_context_,
                variable_types.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_types_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_type", knitro_return_code);
        return variable_type;
    }

    /** Set a property on a variable (e.g. KN_VAR_LINEAR). */
    void set_var_property(
            VariableId variable_id,
            int property)
    {
        int knitro_return_code = KN_set_var_property(
                knitro_context_,
                variable_id,
                property);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_property", knitro_return_code);
    }

    /** Set properties on a subset of variables. */
    void set_var_properties(
            const std::vector<VariableId>& variable_ids,
            const std::vector<int>& properties)
    {
        int knitro_return_code = KN_set_var_properties(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                properties.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_properties", knitro_return_code);
    }

    /** Set properties on all variables. */
    void set_var_properties(
            const std::vector<int>& properties)
    {
        int knitro_return_code = KN_set_var_properties_all(
                knitro_context_,
                properties.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_properties_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_lobnd", knitro_return_code);
    }

    /** Set the lower bounds of a subset of constraints. */
    void set_con_lobnds(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<double>& lower_bounds)
    {
        int knitro_return_code = KN_set_con_lobnds(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                lower_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_lobnds", knitro_return_code);
    }

    /** Set the lower bounds of all constraints. */
    void set_con_lobnds(
            const std::vector<double>& lower_bounds)
    {
        int knitro_return_code = KN_set_con_lobnds_all(
                knitro_context_,
                lower_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_lobnds_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_upbnd", knitro_return_code);
    }

    /** Set the upper bounds of a subset of constraints. */
    void set_con_upbnds(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<double>& upper_bounds)
    {
        int knitro_return_code = KN_set_con_upbnds(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                upper_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_upbnds", knitro_return_code);
    }

    /** Set the upper bounds of all constraints. */
    void set_con_upbnds(
            const std::vector<double>& upper_bounds)
    {
        int knitro_return_code = KN_set_con_upbnds_all(
                knitro_context_,
                upper_bounds.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_upbnds_all", knitro_return_code);
    }

    /** Set an equality bound on a constraint. */
    void set_con_eqbnd(
            ConstraintId constraint_id,
            double value)
    {
        int knitro_return_code = KN_set_con_eqbnd(
                knitro_context_,
                constraint_id,
                value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_eqbnd", knitro_return_code);
    }

    /** Set equality bounds on a subset of constraints. */
    void set_con_eqbnds(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_con_eqbnds(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_eqbnds", knitro_return_code);
    }

    /** Set equality bounds on all constraints. */
    void set_con_eqbnds(
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_con_eqbnds_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_eqbnds_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_lobnd", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_upbnd", knitro_return_code);
        return upper_bound;
    }

    /** Get the equality bound of a constraint. */
    double get_con_eqbnd(
            ConstraintId constraint_id) const
    {
        double value = 0.0;
        int knitro_return_code = KN_get_con_eqbnd(
                knitro_context_,
                constraint_id,
                &value);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_eqbnd", knitro_return_code);
        return value;
    }

    /** Set the objective goal (KN_OBJGOAL_MINIMIZE or KN_OBJGOAL_MAXIMIZE). */
    void set_obj_goal(
            int objective_goal)
    {
        int knitro_return_code = KN_set_obj_goal(
                knitro_context_,
                objective_goal);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_obj_goal", knitro_return_code);
    }

    /** Get the objective goal (KN_OBJGOAL_MINIMIZE or KN_OBJGOAL_MAXIMIZE). */
    int get_obj_goal() const
    {
        int objective_goal = -1;
        int knitro_return_code = KN_get_obj_goal(
                knitro_context_,
                &objective_goal);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_obj_goal", knitro_return_code);
        return objective_goal;
    }

    /** Set properties on the objective function. */
    void set_obj_property(int property)
    {
        int knitro_return_code = KN_set_obj_property(
                knitro_context_,
                property);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_obj_property", knitro_return_code);
    }

    /** Set a property on a constraint. */
    void set_con_property(
            ConstraintId constraint_id,
            int property)
    {
        int knitro_return_code = KN_set_con_property(
                knitro_context_,
                constraint_id,
                property);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_property", knitro_return_code);
    }

    /** Set properties on a subset of constraints. */
    void set_con_properties(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<int>& properties)
    {
        int knitro_return_code = KN_set_con_properties(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                properties.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_properties", knitro_return_code);
    }

    /** Set properties on all constraints. */
    void set_con_properties(
            const std::vector<int>& properties)
    {
        int knitro_return_code = KN_set_con_properties_all(
                knitro_context_,
                properties.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_properties_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_primal_init_value", knitro_return_code);
    }

    /** Set the initial primal values of a subset of variables. */
    void set_var_primal_init_values(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_var_primal_init_values(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_primal_init_values", knitro_return_code);
    }

    /** Set the intial values of the primal variables. */
    void set_var_primal_init_values(
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_var_primal_init_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_primal_init_values_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_dual_init_value", knitro_return_code);
    }

    /** Set the initial dual values of a subset of variables. */
    void set_var_dual_init_values(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_var_dual_init_values(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_dual_init_values", knitro_return_code);
    }

    /** Set the initial dual values of all variables. */
    void set_var_dual_init_values(
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_var_dual_init_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_dual_init_values_all", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_dual_init_value", knitro_return_code);
    }

    /** Set the initial dual values of a subset of constraints. */
    void set_con_dual_init_values(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_con_dual_init_values(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_dual_init_values", knitro_return_code);
    }

    /** Set the initial dual values of all constraints. */
    void set_con_dual_init_values(
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_con_dual_init_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_dual_init_values_all", knitro_return_code);
    }

    /*
     * Adding/removing/changing constant structure
     */

    /** Add a constant to the objective function. */
    void add_obj_constant(
            const double constant)
    {
        int knitro_return_code = KN_add_obj_constant(
                knitro_context_,
                constant);
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_obj_constant", knitro_return_code);
    }

    /** Delete all constant terms from the objective function. */
    void del_obj_constant()
    {
        int knitro_return_code = KN_del_obj_constant(knitro_context_);
        if (knitro_return_code != 0)
            throw KnitroException("KN_del_obj_constant", knitro_return_code);
    }

    /** Change the constant term in the objective function. */
    void chg_obj_constant(const double constant)
    {
        int knitro_return_code = KN_chg_obj_constant(
                knitro_context_,
                constant);
        if (knitro_return_code != 0)
            throw KnitroException("KN_chg_obj_constant", knitro_return_code);
    }

    /** Add a constant to a constraint function. */
    void add_con_constant(
            ConstraintId constraint_id,
            const double constant)
    {
        int knitro_return_code = KN_add_con_constant(
                knitro_context_,
                constraint_id,
                constant);
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_constant", knitro_return_code);
    }

    /** Delete all constant terms from a constraint function. */
    void del_con_constant(ConstraintId constraint_id)
    {
        int knitro_return_code = KN_del_con_constant(
                knitro_context_,
                constraint_id);
        if (knitro_return_code != 0)
            throw KnitroException("KN_del_con_constant", knitro_return_code);
    }

    /** Change the constant term in a constraint function. */
    void chg_con_constant(
            ConstraintId constraint_id,
            const double constant)
    {
        int knitro_return_code = KN_chg_con_constant(
                knitro_context_,
                constraint_id,
                constant);
        if (knitro_return_code != 0)
            throw KnitroException("KN_chg_con_constant", knitro_return_code);
    }

    /*
     * Adding/removing/changing linear structure
     */

    /** Add linear structure to the objective function (bulk). */
    void add_obj_linear_struct(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_obj_linear_struct(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_obj_linear_struct", knitro_return_code);
    }

    /** Add linear structure to the objective function. */
    void add_obj_linear_term(
            VariableId variable_id,
            const double coefficient)
    {
        int knitro_return_code = KN_add_obj_linear_term (
                knitro_context_,
                variable_id,
                coefficient);
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_obj_linear_term", knitro_return_code);
    }

    /** Add linear structure to multiple constraint functions at once. */
    void add_con_linear_struct(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_con_linear_struct(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                variable_ids.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_linear_struct", knitro_return_code);
    }

    /** Add linear structure to one constraint function (bulk). */
    void add_con_linear_struct_one(
            ConstraintId constraint_id,
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_con_linear_struct_one(
                knitro_context_,
                variable_ids.size(),
                constraint_id,
                variable_ids.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_linear_struct_one", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_linear_term", knitro_return_code);
    }

    /*
     * Adding quadratic structure
     */

    /** Add quadratic structure to the objective (bulk). */
    void add_obj_quadratic_struct(
            const std::vector<VariableId>& variable_ids_1,
            const std::vector<VariableId>& variable_ids_2,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_obj_quadratic_struct(
                knitro_context_,
                variable_ids_1.size(),
                variable_ids_1.data(),
                variable_ids_2.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_obj_quadratic_struct", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_obj_quadratic_term", knitro_return_code);
    }

    /** Add quadratic structure to multiple constraint functions at once. */
    void add_con_quadratic_struct(
            const std::vector<ConstraintId>& constraint_ids,
            const std::vector<VariableId>& variable_ids_1,
            const std::vector<VariableId>& variable_ids_2,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_con_quadratic_struct(
                knitro_context_,
                constraint_ids.size(),
                constraint_ids.data(),
                variable_ids_1.data(),
                variable_ids_2.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_quadratic_struct", knitro_return_code);
    }

    /** Add quadratic structure to one constraint function (bulk). */
    void add_con_quadratic_struct_one(
            ConstraintId constraint_id,
            const std::vector<VariableId>& variable_ids_1,
            const std::vector<VariableId>& variable_ids_2,
            const std::vector<double>& coefficients)
    {
        int knitro_return_code = KN_add_con_quadratic_struct_one(
                knitro_context_,
                variable_ids_1.size(),
                constraint_id,
                variable_ids_1.data(),
                variable_ids_2.data(),
                coefficients.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_quadratic_struct_one", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_con_quadratic_term", knitro_return_code);
    }

    /*
     * Adding conic structure
     */

    /*
     * Adding complementarity constraints
     */

    /*
     * Names
     */

    /** Set the name of a variable. */
    void set_var_name(
            VariableId variable_id,
            const std::string& name)
    {
        int knitro_return_code = KN_set_var_name(
                knitro_context_,
                variable_id,
                name.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_var_name", knitro_return_code);
    }

    /** Get the name of a variable. */
    std::string get_var_name(VariableId variable_id) const
    {
        char buffer[4096];
        int knitro_return_code = KN_get_var_name(
                knitro_context_,
                variable_id,
                sizeof(buffer),
                buffer);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_name", knitro_return_code);
        return std::string(buffer);
    }

    /** Set the name of a constraint. */
    void set_con_name(
            ConstraintId constraint_id,
            const std::string& name)
    {
        int knitro_return_code = KN_set_con_name(
                knitro_context_,
                constraint_id,
                name.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_con_name", knitro_return_code);
    }

    /** Get the name of a constraint. */
    std::string get_con_name(ConstraintId constraint_id) const
    {
        char buffer[4096];
        int knitro_return_code = KN_get_con_name(
                knitro_context_,
                constraint_id,
                sizeof(buffer),
                buffer);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_name", knitro_return_code);
        return std::string(buffer);
    }

    /** Set the name of the objective. */
    void set_obj_name(const std::string& name)
    {
        int knitro_return_code = KN_set_obj_name(
                knitro_context_,
                name.c_str());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_obj_name", knitro_return_code);
    }

    /** Get the name of the objective. */
    std::string get_obj_name() const
    {
        char buffer[4096];
        int knitro_return_code = KN_get_obj_name(
                knitro_context_,
                sizeof(buffer),
                buffer);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_obj_name", knitro_return_code);
        return std::string(buffer);
    }

    /*
     * Adding evaluation callbacks
     */

    using EvalCallback = std::function<int(
            const Context&,
            CB_context_ptr,
            KN_eval_request_ptr const,
            KN_eval_result_ptr const)>;

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
        if (knitro_return_code != 0)
            throw KnitroException("KN_add_eval_callback", knitro_return_code);
        knitro_return_code = KN_set_cb_user_params(
                knitro_context_,
                callback_context,
                eval_callbacks_.back().get());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_cb_user_params", knitro_return_code);
        cb2eval_[callback_context] = eval_callbacks_.back().get();
        return callback_context;
    }

    /** Set gradient callback (dense). */
    void set_cb_grad(
            CB_context* callback_context,
            EvalCallback gradient_callback_function)
    {
        cb2eval_.at(callback_context)->gradient = gradient_callback_function;
        int knitro_return_code = KN_set_cb_grad(
                knitro_context_,
                callback_context,
                KN_DENSE,
                nullptr,
                KN_DENSE,
                nullptr,
                nullptr,
                gradient_callback);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_cb_grad", knitro_return_code);
    }

    /** Set gradient callback (sparse). */
    void set_cb_grad(
            CB_context* callback_context,
            const std::vector<VariableId>& objgrad_variable_ids,
            const std::vector<ConstraintId>& jacobian_constraint_ids,
            const std::vector<VariableId>& jacobian_variable_ids,
            EvalCallback gradient_callback_function)
    {
        cb2eval_.at(callback_context)->gradient = gradient_callback_function;
        int knitro_return_code = KN_set_cb_grad(
                knitro_context_,
                callback_context,
                objgrad_variable_ids.size(),
                objgrad_variable_ids.data(),
                jacobian_constraint_ids.size(),
                jacobian_constraint_ids.data(),
                jacobian_variable_ids.data(),
                gradient_callback);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_cb_grad", knitro_return_code);
    }

    /** Set Hessian callback (dense). */
    void set_cb_hess(
            CB_context* callback_context,
            EvalCallback hessian_callback_function)
    {
        cb2eval_.at(callback_context)->hessian = hessian_callback_function;
        int knitro_return_code = KN_set_cb_hess(
                knitro_context_,
                callback_context,
                KN_DENSE_ROWMAJOR,
                nullptr,
                nullptr,
                hessian_callback);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_cb_hess", knitro_return_code);
    }

    /** Set Hessian callback (sparse). */
    void set_cb_hess(
            CB_context* callback_context,
            const std::vector<VariableId>& variable_ids_1,
            const std::vector<VariableId>& variable_ids_2,
            EvalCallback hessian_callback_function)
    {
        cb2eval_.at(callback_context)->hessian = hessian_callback_function;
        int knitro_return_code = KN_set_cb_hess(
                knitro_context_,
                callback_context,
                variable_ids_1.size(),
                variable_ids_1.data(),
                variable_ids_2.data(),
                hessian_callback);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_cb_hess", knitro_return_code);
    }

    /*
     * Other user callbacks
     */

    using UserCallback = std::function<int(const Context&, const double* const, const double* const)>;

    /** Set the MIP node callback. */
    void set_mip_node_callback(
            UserCallback mip_node_callback_function)
    {
        mip_node_callback_ = mip_node_callback_function;
        int knitro_return_code = KN_set_mip_node_callback(
                knitro_context_,
                mip_node_callback,
                (void* const)this);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_node_callback", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_var_primal_init_value", knitro_return_code);
    }

    /** Set the MIP initial primal values of a subset of variables. */
    void set_mip_var_primal_init_values(
            const std::vector<VariableId>& variable_ids,
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_mip_var_primal_init_values(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_var_primal_init_values", knitro_return_code);
    }

    /** Set the MIP initial primal values of all variables. */
    void set_mip_var_primal_init_values(
            const std::vector<double>& values)
    {
        int knitro_return_code = KN_set_mip_var_primal_init_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_var_primal_init_values_all", knitro_return_code);
    }

    /** Set the branching priority of an integer variable. */
    void set_mip_branching_priority(
            VariableId variable_id,
            int priority)
    {
        int knitro_return_code = KN_set_mip_branching_priority(
                knitro_context_,
                variable_id,
                priority);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_branching_priority", knitro_return_code);
    }

    /** Set the branching priorities of a subset of integer variables. */
    void set_mip_branching_priorities(
            const std::vector<VariableId>& variable_ids,
            const std::vector<int>& priorities)
    {
        int knitro_return_code = KN_set_mip_branching_priorities(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                priorities.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_branching_priorities", knitro_return_code);
    }

    /** Set the branching priorities of all integer variables. */
    void set_mip_branching_priorities(
            const std::vector<int>& priorities)
    {
        int knitro_return_code = KN_set_mip_branching_priorities_all(
                knitro_context_,
                priorities.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_branching_priorities_all", knitro_return_code);
    }

    /** Set the strategy for dealing with an integer variable. */
    void set_mip_intvar_strategy(
            VariableId variable_id,
            int strategy)
    {
        int knitro_return_code = KN_set_mip_intvar_strategy(
                knitro_context_,
                variable_id,
                strategy);
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_intvar_strategy", knitro_return_code);
    }

    /** Set strategies for dealing with a subset of integer variables. */
    void set_mip_intvar_strategies(
            const std::vector<VariableId>& variable_ids,
            const std::vector<int>& strategies)
    {
        int knitro_return_code = KN_set_mip_intvar_strategies(
                knitro_context_,
                variable_ids.size(),
                variable_ids.data(),
                strategies.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_intvar_strategies", knitro_return_code);
    }

    /** Set strategies for dealing with all integer variables. */
    void set_mip_intvar_strategies(
            const std::vector<int>& strategies)
    {
        int knitro_return_code = KN_set_mip_intvar_strategies_all(
                knitro_context_,
                strategies.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_set_mip_intvar_strategies_all", knitro_return_code);
    }

    /*
     * Solving
     */

    /** Update the internal model without solving. */
    void update()
    {
        int knitro_return_code = KN_update(knitro_context_);
        if (knitro_return_code != 0)
            throw KnitroException("KN_update", knitro_return_code);
    }

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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_number_vars", knitro_return_code);
        return number_of_variables;
    }

    /** Get the number of constraints in the model. */
    ConstraintId get_number_cons() const
    {
        ConstraintId number_of_constraints = -1;
        int knitro_return_code = KN_get_number_cons(
                knitro_context_,
                &number_of_constraints);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_number_cons", knitro_return_code);
        return number_of_constraints;
    }

    /** Get the value of the objective. */
    double get_obj_value() const
    {
        double objective = 0.0;
        int knitro_return_code = KN_get_obj_value(
                knitro_context_,
                &objective);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_obj_value", knitro_return_code);
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_primal_value", knitro_return_code);
        return value;
    }

    /** Get the values of all primal variables. */
    std::vector<double> get_var_primal_values() const
    {
        std::vector<double> values(this->get_number_vars(), 0.0);
        int knitro_return_code = KN_get_var_primal_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_primal_values_all", knitro_return_code);
        return values;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_dual_value", knitro_return_code);
        return value;
    }

    /** Get the dual values of all variables. */
    std::vector<double> get_var_dual_values() const
    {
        std::vector<double> values(this->get_number_vars(), 0.0);
        int knitro_return_code = KN_get_var_dual_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_var_dual_values_all", knitro_return_code);
        return values;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_dual_value", knitro_return_code);
        return value;
    }

    /** Get the dual values of all constraints. */
    std::vector<double> get_con_dual_values() const
    {
        std::vector<double> values(this->get_number_cons(), 0.0);
        int knitro_return_code = KN_get_con_dual_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_dual_values_all", knitro_return_code);
        return values;
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
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_value", knitro_return_code);
        return value;
    }

    /** Get the values of all constraints. */
    std::vector<double> get_con_values() const
    {
        std::vector<double> values(this->get_number_cons(), 0.0);
        int knitro_return_code = KN_get_con_values_all(
                knitro_context_,
                values.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_con_values_all", knitro_return_code);
        return values;
    }

    /** Get the absolute feasibility error at the solution. */
    double get_abs_feas_error() const
    {
        double abs_feas_error = -1;
        int knitro_return_code = KN_get_abs_feas_error(
                knitro_context_,
                &abs_feas_error);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_abs_feas_error", knitro_return_code);
        return abs_feas_error;
    }

    /** Get the relative feasibility error at the solution. */
    double get_rel_feas_error() const
    {
        double rel_feas_error = -1;
        int knitro_return_code = KN_get_rel_feas_error(
                knitro_context_,
                &rel_feas_error);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_rel_feas_error", knitro_return_code);
        return rel_feas_error;
    }

    /** Get the absolute optimality error at the solution. */
    double get_abs_opt_error() const
    {
        double abs_opt_error = -1;
        int knitro_return_code = KN_get_abs_opt_error(
                knitro_context_,
                &abs_opt_error);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_abs_opt_error", knitro_return_code);
        return abs_opt_error;
    }

    /** Get the relative optimality error at the solution. */
    double get_rel_opt_error() const
    {
        double rel_opt_error = -1;
        int knitro_return_code = KN_get_rel_opt_error(
                knitro_context_,
                &rel_opt_error);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_rel_opt_error", knitro_return_code);
        return rel_opt_error;
    }

    /** Get the number of iterations made by KN_solve. */
    int get_number_iters() const
    {
        int num_iters = 0;
        int knitro_return_code = KN_get_number_iters(
                knitro_context_,
                &num_iters);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_number_iters", knitro_return_code);
        return num_iters;
    }

    /** Get the CPU time spent in KN_solve. */
    double get_solve_time_cpu() const
    {
        double time = 0.0;
        int knitro_return_code = KN_get_solve_time_cpu(
                knitro_context_,
                &time);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_solve_time_cpu", knitro_return_code);
        return time;
    }

    /** Get the real (wall clock) time spent in KN_solve. */
    double get_solve_time_real() const
    {
        double time = 0.0;
        int knitro_return_code = KN_get_solve_time_real(
                knitro_context_,
                &time);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_solve_time_real", knitro_return_code);
        return time;
    }

    /** Get the objective value of the MIP incumbent solution. */
    bool has_mip_incumbent() const
    {
        double incumbent_objective;
        int knitro_return_code = KN_get_mip_incumbent_obj(
                knitro_context_,
                &incumbent_objective);
        if (knitro_return_code < 0)
            throw KnitroException("KN_get_mip_incumbent_obj", knitro_return_code);
        return (knitro_return_code == 0);
    }

    /** Get the objective value of the MIP incumbent solution. */
    double get_mip_incumbent_obj() const
    {
        double incumbent_objective;
        int knitro_return_code = KN_get_mip_incumbent_obj(
                knitro_context_,
                &incumbent_objective);
        if (knitro_return_code < 0)
            throw KnitroException("KN_get_mip_incumbent_obj", knitro_return_code);
        return incumbent_objective;
    }

    /** Get the value of the current MIP relaxation bound. */
    double get_mip_relaxation_bnd() const
    {
        double relaxation_bound = 0.0;
        int knitro_return_code = KN_get_mip_relaxation_bnd(
                knitro_context_,
                &relaxation_bound);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_relaxation_bnd", knitro_return_code);
        return relaxation_bound;
    }

    /** Get the objective value of the most recently solved MIP node subproblem. */
    double get_mip_lastnode_obj() const
    {
        double last_node_obj = 0.0;
        int knitro_return_code = KN_get_mip_lastnode_obj(
                knitro_context_,
                &last_node_obj);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_lastnode_obj", knitro_return_code);
        return last_node_obj;
    }

    /** Get the number of nodes processed in the MIP solve. */
    int get_mip_number_nodes() const
    {
        int num_nodes = 0;
        int knitro_return_code = KN_get_mip_number_nodes(
                knitro_context_,
                &num_nodes);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_number_nodes", knitro_return_code);
        return num_nodes;
    }

    /** Get the final absolute optimality gap in the MIP solve. */
    double get_mip_abs_gap() const
    {
        double abs_gap = 0.0;
        int knitro_return_code = KN_get_mip_abs_gap(
                knitro_context_,
                &abs_gap);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_abs_gap", knitro_return_code);
        return abs_gap;
    }

    /** Get the final relative optimality gap in the MIP solve. */
    double get_mip_rel_gap() const
    {
        double rel_gap = 0.0;
        int knitro_return_code = KN_get_mip_rel_gap(
                knitro_context_,
                &rel_gap);
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_rel_gap", knitro_return_code);
        return rel_gap;
    }

    /** Get the MIP incumbent solution. */
    std::vector<double> get_mip_incumbent_x() const
    {
        std::vector<double> mip_incumbent_x(get_number_vars(), 0.0);
        int knitro_return_code = KN_get_mip_incumbent_x(
                knitro_context_,
                mip_incumbent_x.data());
        if (knitro_return_code != 0)
            throw KnitroException("KN_get_mip_incumbent_x", knitro_return_code);
        return mip_incumbent_x;
    }

private:

    struct EvalCallbackStruct
    {
        EvalCallback eval_callback;
        EvalCallback gradient;
        EvalCallback hessian;
    };

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

    /** Constructor from an already existing C context. */
    Context(KN_context* knitro_context):
        knitro_context_(knitro_context),
        own_context_(false) { }

};

}
